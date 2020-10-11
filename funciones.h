#ifndef PROYECTO_1_FUNCIONES_H
#define PROYECTO_1_FUNCIONES_H

#include <fstream>
using namespace std;

int getFileSize(const std::string& fileName) {
    ifstream file(fileName.c_str(), ifstream::in | ifstream::binary);

    if(!file.is_open()) return -1;

    file.seekg(0, ios::end);
    int fileSize = file.tellg();
    file.close();

    return fileSize;
}

void writeCharArray(fstream& stream, const char* str, int len) {
    stream.write(str, len);
}

char* readCharArray(fstream& stream, int len) {
    char* buffer = new char[len+1];
    stream.read(buffer, len);
    buffer[len] = '\0';
    return buffer;
}

void writeInt(fstream& stream, int ival) {
    stream.write(reinterpret_cast<char*>(&ival), sizeof(int));
}

int readInt(fstream& stream) {
    int result;
    stream.read((char*) &result, sizeof(int));
    return result;
}

void writeShort(fstream& stream, short ival) {
    stream.write(reinterpret_cast<char*>(&ival), sizeof(short));
}

short readShort(fstream& stream) {
    short result;
    stream.read((char*) &result, sizeof(short));
    return result;
}

template <typename T>
void writeTArray(fstream& stream, const T* array, int len) {
    stream.write( (char*) array, len * sizeof(T));
}

template <typename T>
T* readTArray (fstream& stream, int len) {
    T* buffer = new T[len];
    stream.read( (char*) buffer, len * sizeof(T));
    return buffer;
}

#endif //PROYECTO_1_FUNCIONES_H
