#include <chrono>
#include <cassert>
#include "BPlusTree.h"

using namespace std;

typedef btree<unsigned>::iterator btree_iterator;

int main() {
     fstream fixedLength("datos.dat", fstream::in | fstream::binary);

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

               // cout << "Registro longitud fija: ";
               // seteamos el id a mano, ya que nuestro dataset tiene id's repetidos
               reg->id = i+1;
               registros.push_back(reg);
               // reg->print();
          }
     }

     fixedLength.close();

     /// PRUEBAS DE INSERCION

     btree<unsigned> bt; // le tenemos que pasar al B+ el tipo de dato del key

     auto start = chrono::high_resolution_clock::now();

     for (int i = 0; i < 200; ++i) {
          bt.insert(registros[i]);
     }

     auto end = chrono::high_resolution_clock::now();
     auto executionTime = chrono::duration_cast<chrono::milliseconds>(end - start);
     cout << "Insertion time for 200 registers: " << executionTime.count() << " ms.\n";
     cout << "Reads: " << reads << "\n";
     cout << "Writes: " << writes << "\n";
     reads = 0;
     writes = 0;

     // bt.print();

     /// PRUEBAS DE BUSQUEDA

     start = chrono::high_resolution_clock::now();

     for (int i = 0; i < 200; ++i) {
          unsigned id = registros[i]->id;

          btree_iterator node = bt.find(id);

          assert(node.ptr->registros[node.index]->id == id);
     }

     end = chrono::high_resolution_clock::now();
     executionTime = chrono::duration_cast<chrono::milliseconds>(end - start);

     cout << "Search time for 200 registers: " << executionTime.count() << " ms.\n";
     cout << "Reads: " << reads << "\n";
     cout << "Writes: " << writes << "\n";

     return 0;
}
