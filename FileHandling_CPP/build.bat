@echo off 

del fReadWrite.exe
g++ -o fReadWrite fReadWrite.cpp
fReadWrite.exe
color 2