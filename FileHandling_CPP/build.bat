@echo off 

del test.exe
g++ -o test test.cpp
test.exe
color 2