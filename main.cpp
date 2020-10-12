#include <vector>
#include <iostream>
#include "BPlusTree.h"

using namespace std;

int main() {

    // typedef btree<int>::iterator btree_iterator;
    // ORDER = 3;
    // btree<int> bt;
    // for (size_t i = 1; i <= 10; i++) {
    //     bt.insert(i);
    // }



    // bt.print();
    // bt.remove(1);
    // cout << "==============================" << endl;
    // bt.print();
    // bt.remove(4);
    // cout << "==============================" << endl;
    // bt.print();
    // bt.remove(2);
    // cout << "==============================" << endl;
    // bt.print();
    // bt.remove(9);
    // cout << "==============================" << endl;
    // bt.print();
    
    // bt.in_order_print();

    // bt.print();
    // bt.print_leaves();

    // btree_iterator beg = bt.find(10);
    // btree_iterator end = bt.find(25);

    // for (btree_iterator it = beg; it != end; it++) {
    //     if (*it != 0) {
    //         cout << *it << " ";
    //     }
    // }
    // cout << "\n";

    // bt.insert(-1);
    // bt.print();
    // bt.print_leaves();

    // bt.remove(-1);
    // bt.insert(-2);
    
    // bt.print();

    // bt.remove(1);
    // bt.remove(5);

    // bt.print();

    // Análisis Teórico:
        // RAM:
        // DISK:

    // int n;
    // std::cin >> n >> ORDER;

    // btree<int> bt;

    // int e;
    // for (int i = 0; i < n; ++i) {
    //     std::cin >> e;
    //     bt.insert(e);
    // }

    // bt.in_order_print();

    fstream file("nodos.dat", fstream::binary | fstream::out | fstream::in | fstream::trunc);

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

    btree<int> bt;

    return 0;
}