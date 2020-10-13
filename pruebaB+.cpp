#include <bits/stdc++.h>
#include <chrono>

using namespace std;

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

void writeShort(fstream& stream, int ival) {
     stream.write(reinterpret_cast<char*>(&ival), sizeof(short));
}

int readShort(fstream& stream) {
     int result;
     stream.read((char*) &result, sizeof(short));
     return result;
}

struct Registro {
     unsigned id;
     char name[20];
     short pin;
     char country[35];

     Registro() {
          // this->id = 5;
          // char name[21] = "12345678912345678912";
          // char country[36] = "12345678912345678912111111111111111";
          // this->pin = 69;
          // strncpy(this->name, name, 20);
          // strncpy(this->country, country, 20);
     }

     Registro(unsigned id, string name, short pin, string country) {
          this->id = id;
          strncpy(this->name, name.c_str(), 20);
          this->pin = pin;
          strncpy(this->country, country.c_str(), 35);
     }

     void write(fstream& file) {
          writeInt(file, this->id);
          writeCharArray(file, this->name, 20);
          writeShort(file, this->pin);
          writeCharArray(file, this->country, 35);
     }

     void read(fstream& file) {
          this->id = readInt(file);
          strncpy(this->name, readCharArray(file, 20), 20);
          this->pin = readShort(file);
          strncpy(this->country, readCharArray(file, 35), 35);
     }

     void print() {
          cout << id << " ";
          cout << name << " ";
          cout << pin << " ";
          cout << country << "\n";
     }
};

int main() {

     fstream fixedLength("datos.dat", fstream::in | fstream::binary);

     vector<Registro*> registros;


     auto start = chrono::high_resolution_clock::now();
     if (fixedLength.is_open()) {
          int readOffset = 0;
          start = chrono::high_resolution_clock::now();
          for (int i = 0; i < 200; ++i) {
               // leer todo el fixed length
               Registro* reg = new Registro();
               // lee el registro que acabas de escribir
               fixedLength.seekg(readOffset, ios::beg);
               reg->id = readInt(fixedLength);
               readOffset += sizeof(int);
               strncpy(reg->name, readCharArray(fixedLength, 20), 20);
               readOffset += 20;
               reg->pin = readShort(fixedLength);
               readOffset += sizeof(short);
               strncpy(reg->country, readCharArray(fixedLength, 35), 35);
               readOffset += 35;

               cout << "Registro longitud fija: ";
               registros.push_back(reg);
               reg->print();
          }

          // TODO: si sobra tiempo, hacer el iterador en el B+, no creo que sea mucha chamba
          // TODO: por cada registro en el vector 'registros', insertarlo en el B+
          auto end = chrono::high_resolution_clock::now();
          auto executionTime = chrono::duration_cast<chrono::milliseconds>(end - start);
          cout << "Execution time: " << executionTime.count() << " ms.\n";
          fixedLength.seekg(0, ios::end);
          int fileSize = fixedLength.tellg();
          cout << "Fixed length size in bytes: " << fileSize << "\n";
          cout << "Number registers in fixedLength file: " << fileSize/(sizeof(Registro)-3) << "\n";
     }

     fixedLength.close();

     return 0;
}