#include <iostream>
#include <fstream>

#define UPLOAD_DATA_RATE 23
#define UPLOAD_FILE_PATH "D:\\LorawanProject\\test\\ExploreCpp\\FileHandling_CPP\\fRead.bin"

#define DOWNLOAD_DATA_RATE 16
#define DOWNLOAD_FILE_PATH "D:\\LorawanProject\\test\\ExploreCpp\\FileHandling_CPP\\fRead.bin"

bool downloadApi(const char * downloadFilePath, uint8_t * downloadBuff, uint8_t downloadDataRate) {
    std::fstream downFile;

    downFile.open(downloadFilePath, std::ios::out | std::ios::binary);

    for(uint8_t i=0; i<downloadDataRate; i++) {
        downFile << downloadBuff[i];
    }

    downFile.close();

    std::cout << "\n********************** file download done !! **********************\n";
    return true;
}

void sendApi(uint8_t * buf, uint8_t bufLen) {
    for(uint8_t i=0; i<bufLen; i++) {
        std::cout << buf[i];
    }
    std::cout << std::endl;
}

bool uploadApi(const char * uploadFilePath, uint8_t uploadDataRate) {
    std::fstream upFile;
    uint8_t magicIdx = 0;
    uint8_t * uploadBuff  = NULL;

    // allocate memory for the upload data buffer 
    uploadBuff = new uint8_t[uploadDataRate];

    // open the file to be uploaded
    upFile.open(uploadFilePath, std::ios::in | std::ios::binary);

    // read the data set and send it to the device unitl you not met EOF
    while (!upFile.eof()) { 
        // file object validation
        if (!upFile) {
            std::cout << "Error in file reading : " << uploadFilePath << std::endl;
            return false;
        }  

        // raed byte by byte and generate a upload data buffer
        magicIdx = 0;
        for(uint8_t i=0; i<uploadDataRate; i++) {
            upFile >> uploadBuff[magicIdx++];
        }

        // at last send that upload data buffer
        sendApi(uploadBuff, uploadDataRate);                      
    }

    // de-allocate memory for the upload data buffer 
    delete [] uploadBuff;

    // open the file to be uploaded
    upFile.close();

    std::cout << "\n********************** file upload done !! **********************\n";
    return true;
}

int main() {
    bool status = false;
    status = uploadApi(UPLOAD_FILE_PATH, UPLOAD_DATA_RATE);
    std::cout << "upload status : " << status << std::endl;
    return 0;
}