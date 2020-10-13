#include <vector>
#include <iostream>
#include <cassert>

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
    cout << *beg << "\n";

    beg.ptr->registros[beg.index]->print();

    assert (beg.ptr->registros[beg.index]->id == 78);

    btree_iterator result = bt.find(82);
    cout << *result << "\n";

    // result.ptr->registros[result.index]->print();

    // assert (result.ptr->registros[0]->id == 87);

    return 0;
}
