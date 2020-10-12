#include <vector>
#include <iostream>
#include "BPlusTree.h"

using namespace std;

int main() {
    btree<int> bt;
    auto r1 = new Registro(69, "Benjamin", 1234, "Pisco");
    auto r2 = new Registro(70, "Yanli", 5432, "Ica");
    auto r3 = new Registro(71, "Yeny", 6789, "Arequipa");
    auto r4 = new Registro(72, "Victor", 9876, "Huacho");
    auto r5 = new Registro(73, "Jose Maria", 1111, "Lambayeque");
    auto r6 = new Registro(74, "Benjamin", 1234, "Pisco");
    auto r7 = new Registro(75, "Yanli", 5432, "Ica");
    auto r8 = new Registro(76, "Yeny", 6789, "Arequipa");
    auto r9 = new Registro(77, "Victor", 9876, "Huacho");
    auto r10 = new Registro(78, "Jose Maria", 1111, "Lambayeque");
    auto r11 = new Registro(79, "Benjamin", 1234, "Pisco");
    auto r12 = new Registro(80, "Yanli", 5432, "Ica");
    auto r13 = new Registro(81, "Yeny", 6789, "Arequipa");
    auto r14 = new Registro(82, "Victor", 9876, "Huacho");
    auto r15 = new Registro(83, "Jose Maria", 1111, "Lambayeque");
    auto r16 = new Registro(84, "Jose Maria", 1111, "Lambayeque");

    bt.insert(r1);
    bt.insert(r2);
    bt.insert(r3);
    bt.insert(r4);
    bt.insert(r5);
    bt.insert(r6);
    bt.insert(r7);
    bt.insert(r8);
    bt.insert(r9);
    bt.insert(r10);
    bt.insert(r11);
    bt.insert(r12);
    bt.insert(r13);
    bt.insert(r14);
    bt.insert(r15);
    for (int i = 0; i < 15; ++i) {
        r16->id++;
        bt.insert(r16);
    }
    bt.print();

    typedef btree<int>::iterator btree_iterator;

    btree_iterator beg = bt.find(78);
    cout << *beg << "\n"; // deberia printear 78

    // bt.print_leaves();
    return 0;
}

/*
 *     fstream file("nodos.dat", fstream::binary | fstream::out | fstream::in | fstream::trunc);

    if (file.is_open()) {

        // int* arr = new int[5];
        // arr[0] = 5;
        // arr[1] = 4;
        // arr[2] = 3;
        // arr[3] = 2;
        // arr[4] = 1;

        // writeTArray<int>(file, arr, 5);
        // file.seekg(0, ios::beg);

        // int* arrLeido = readTArray<int>(file, 5);

        // for (int i = 0; i < 5; ++i) {
        //     cout << arrLeido[i] << " ";
        // }
        // cout << "\n";

        // Registro* r1 = new Registro(69, "Benjamin", 1234, "Pisco");
        // Registro* r2 = new Registro(70, "Yanli", 5432, "Ica");
        // Registro* r3 = new Registro(71, "Yeny", 6789, "Arequipa");
        // Registro* r4 = new Registro(72, "Victor", 9876, "Huacho");
        // Registro* r5 = new Registro(73, "Jose Maria", 1111, "Lambayeque");

        // Registro** registers = new Registro*[5];
        // registers[0] = r1;
        // registers[1] = r2;
        // registers[2] = r3;
        // registers[3] = r4;
        // registers[4] = r5;

        // writeRegisterArray(file, registers, 5);

        // Registro** registros;

        // file.seekg(0, ios::beg);
        // registros = readRegisterArray(file, 5);

        // for (int i = 0; i < 5; ++i) {
        //     registros[i]->print();
        // }



        // cout << "sizeof(size_t): " << sizeof(size_t) << "\n";
        // cout << "sizeof(uint8_t): " << sizeof(uint8_t) << "\n";

    }

    file.close();
 */