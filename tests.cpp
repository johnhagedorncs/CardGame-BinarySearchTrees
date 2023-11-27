// tests.cpp
#include <iostream>
#include "cards.h"

using namespace std;

int main() {
    CardBST testTree;

    // Insert some cards
    testTree.insert(1, 10);
    testTree.insert(2, 5);
    testTree.insert(3, 8);
    testTree.insert(4, 2);
    testTree.insert(1, 5);
    testTree.insert(2, 7);
    testTree.insert(3, 12);
    testTree.insert(4, 11);

    // Print in order
    cout << "In-order traversal:" << endl;
    testTree.printInOrder();

    // Test find function
    cout << "Find 2 7: " << (testTree.find(2, 7) ? "Found" : "Not found") << endl;
    cout << "Find 3 10: " << (testTree.find(3, 10) ? "Found" : "Not found") << endl;

    // Test successors and predecessors
    Node* successor = testTree.succ(3, 8);
    cout << "Successor of 3 8: " << successor->suit << " " << successor->value << endl;

    Node* predecessor = testTree.pred(2, 5);
    cout << "Predecessor of 2 5: " << predecessor->suit << " " << predecessor->value << endl;

    // Test remove function
    testTree.removeNode(3, 8);
    cout << "After removing 3 8:" << endl;
    testTree.printInOrder();

    return 0;
}
