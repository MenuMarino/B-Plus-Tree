#include <vector>
#include <iostream>
#include <cstring>
#include "BPlusTree.h"
#include "ExtendibleHash.h"

using namespace std;


int main() {
    int c=0;
    fstream rawDataFile, dataFile;
    vector<Registro> aux;
    rawDataFile.open("datosReales.txt", ios::in  | ios::binary);
    int size = getFileSize("datosReales.txt")/sizeof(Registro);
    Registro bb;

    for (int i = 0; i < size; ++i) {
        rawDataFile.read((char*)&bb,sizeof(bb));
        aux.push_back(bb);
        //bb.print();
    }


    StaticHash a(50);
    //a.buildHash();
  // cout << sizeof(Registro);
    a.loadHash();
   // a.showData();
   // cout << cont;
//
//    cout << a.hashMap.size();
//
    for(auto it: aux){
        c++;
        a.search(it.id);
    }

    cout <<c;





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