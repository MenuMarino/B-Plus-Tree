#include <vector>
#include <iostream>
#include "BPlusTree.h"

using namespace std;

int main() {

    // typedef btree<int, 3>::iterator btree_iterator;

    // btree<int, 3> bt;
    // for (size_t i = 0; i <= 30; i++) {
    //     bt.insert(i);
    // }
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

    int n;
    std::cin >> n >> ORDER;

    btree<int> bt;

    int e;
    for (int i = 0; i < n; ++i) {
        std::cin >> e;
        bt.insert(e);
    }

    bt.print();

    return 0;
}