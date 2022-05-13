#include <fstream>
#include <iostream>

#define READ_SIZE 200

std::fstream rdFile;
std::fstream wtFile;

uint8_t readCnt = 0;
bool workDone = false;
bool reqStatus = false;
uint8_t data[READ_SIZE] = {};

bool readFromFile() {
    if (!rdFile) {
        std::cout << "Error in file opening : readFromFile()" << std::endl;
        return false;
    }

    char ch;

    for(int i=0; i<READ_SIZE; i++) {
        if(!rdFile.get(ch)) {
            workDone = true;
            return true;
        }

        data[readCnt++] = ch;
    }
    return true;
}

bool writeToFile(){
    if (!wtFile) {
        std::cout << "Error in file opening : writeToFile()" << std::endl;
        return false;
    }   

    for(int i=0; i<readCnt; i++) {
        std::cout << data[i];
    }
    std::cout << std::endl;

    for(int i=0; i<readCnt; i++) {
        wtFile << data[i];
    }

    return true;
}

int main() {
    rdFile.open("fRead.bin", std::ios::in | std::ios::binary);
    wtFile.open("fWrite.bin", std::ios::out | std::ios::binary);

    while(!workDone) {
        readCnt = 0;
        reqStatus = false;

        reqStatus = readFromFile();
        if(!reqStatus) {
            std::cout << "Aborting : readFromFile()" << std::endl;
            workDone = true;
        }

        reqStatus = writeToFile();
        if(!reqStatus) {
            std::cout << "Aborting : writeToFile()" << std::endl;
            workDone = true;
        }
    }

    rdFile.close(); 
    wtFile.close(); 

    std::cout << "file read operation done !" << std::endl;

    return 0;
}