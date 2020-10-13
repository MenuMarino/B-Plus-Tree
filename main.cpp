#include <vector>
#include <iostream>
#include <cstring>
#include "BPlusTree.h"
#include <chrono>
#include "StaticHash.h"

using namespace std;


int main() {


    int c=0;
    StaticHash a(50);
    fstream rawDataFile, dataFile;
    vector<Registro> aux;
    rawDataFile.open("datosReales.txt", ios::in  | ios::binary);
    int size = getFileSize("datosReales.txt")/sizeof(Registro);
    Registro bb;

    for (int i = 0; i < size; ++i) {
        rawDataFile.read((char*)&bb,sizeof(bb));
       // a.insert(bb);
        aux.push_back(bb);
    }

   // a.saveHash();

   a.loadHash();

    srand(time(0));

    int ind = rand() % 200;

  //  cout << ind;

    auto start = chrono::high_resolution_clock::now();

    for(auto it: aux){
      //  a.insert(it);
      //  c++;
        if(!a.search(it.id)){
            cout << "NO ENCONTRADO";
            break;
        }
    }

   //  a.insert( aux[ind]);

//    if(!a.search(aux[ind].id)){
//        cout<< "NO ENCONTRADO";
//    }

    // busqueda de los 200 elementos
    auto end = chrono::high_resolution_clock::now();
    auto executionTime = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Execution time: " << executionTime.count() << " ms.\n";

    cout << readcant << " " << writecant;

   // cout <<c;





//
//    typedef btree<int>::iterator btree_iterator;
//    ORDER = 3;
//    btree<int> bt;
//    for (size_t i = 1; i <= 10; i++) {
//        bt.insert(i);
//    }
//
//    bt.print();
//    bt.remove(1);
//    cout << "==============================" << endl;
//    bt.print();
//    bt.remove(4);
//    cout << "==============================" << endl;
//    bt.print();
//    bt.remove(2);
//    cout << "==============================" << endl;
//    bt.print();
//    bt.remove(9);
//    cout << "==============================" << endl;
//    bt.print();

   // cout << sizeof(unsigned) << endl;
    
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

    return 0;
}