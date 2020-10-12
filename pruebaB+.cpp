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

     cout << "sizeof(Registro): " << sizeof(Registro) << "\n";


     fstream file("pene.csv");
     fstream fixedLength("datos.dat", fstream::out | fstream::in | fstream::binary | fstream::trunc);
     char delim = ',';

     if (file.is_open() && fixedLength.is_open()) {
          string id, name, pin, country;
          int writeOffset = 0;
          int readOffset = 0;
          while (getline(file, id, delim)) {
               getline(file, name, delim);
               getline(file, pin, delim);
               getline(file, country);
               // if (country[country.length()-1] == '\n') {
               //      country.pop_back();
               // }

               // lee el registro del csv
               Registro registro = Registro(stoi(id), name, stoi(pin), country);
               cout << "Registro original: ";
               registro.print();

               // escribe el registro
               fixedLength.seekp(writeOffset, ios::beg);
               writeInt(fixedLength, registro.id);
               writeOffset += sizeof(int);
               writeCharArray(fixedLength, registro.name, 20);
               writeOffset += 20;
               writeShort(fixedLength, registro.pin);
               writeOffset += sizeof(short);
               writeCharArray(fixedLength, registro.country, 35);
               writeOffset += 35;

               Registro reg = Registro();
               // lee el registro que acabas de escribir
               fixedLength.seekg(readOffset, ios::beg);
               reg.id = readInt(fixedLength);
               readOffset += sizeof(int);
               strncpy(reg.name, readCharArray(fixedLength, 20), 20);
               readOffset += 20;
               reg.pin = readShort(fixedLength);
               readOffset += sizeof(short);
               strncpy(reg.country, readCharArray(fixedLength, 35), 35);
               readOffset += 35;

               // cout << "Registro longitud fija: ";
               // reg.print();
          }
     } else {
          cout << "No se abrió el archivo.\n";
     }

     vector<Registro*> registros;

     if (fixedLength.is_open()) {
          int readOffset = 0;
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

          auto start = chrono::high_resolution_clock::now();
          // TODO: por cada registro en el vector 'registros', insertarlo en el B+
          auto end = chrono::high_resolution_clock::now();
          auto executionTime = chrono::duration_cast<chrono::milliseconds>(end - start);
          cout << "Execution time: " << executionTime.count() << " ms.\n";
          fixedLength.seekg(0, ios::end);
          int fileSize = fixedLength.tellg();
          cout << "Fixed length size in bytes: " << fileSize << "\n";
          cout << "Number registers in fixedLength file: " << fileSize/(sizeof(Registro)-3) << "\n";
     }

     file.close();
     fixedLength.close();

     return 0;
}