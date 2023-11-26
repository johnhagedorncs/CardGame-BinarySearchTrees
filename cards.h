// cards.h
// Author: John Hagedorn
// All class declarations go here

#define UTILITY_H
#include "utility.h"
#include <string>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int suit;
    int value;
    Node* left;
    Node* right;
    Node* parent;

    Node(int suitNum = 0, int valueNum = 0) {
        suit = suitNum;
        value = valueNum;
        right = nullptr;
        left = nullptr;
        parent = nullptr;
    }
};

class CardBST {
public:
    CardBST();
    ~CardBST();
    bool find(int val1, int val2);
    void removeNode(int val1, int val2);
    bool insert(int val1, int val2);
    Node* succ(int val1, int val2);
    Node* pred(int val1, int val2);
    void printInOrder();
    void printInOrder(Node* n);
    string valToString (int valueNum);
    string suitToString (int suitValue);
    void printPred(int val1, int val2);
    void printSucc(int val1, int val2);
    void clearNode(Node *n);
    Node* getNode(int val1, int val2, Node* n);
    Node* getMin() {
        return min(root);
    };
    Node* getMax() {
        return max(root);
    };

private:
    Node* root;
    Node* min(Node *n);
    Node* max(Node *n);
    Node* remove(int val1, int val2, Node* n);
    bool insert(int val1, int val2, Node* n);
    bool findNode(int val1, int val2, Node* n);
};