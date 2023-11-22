// cards.h
// Author: John Hagedorn
// All class declarations go here

#define UTILITY_H
#include "utility.h"
#include <string>
#include <string>
#include <iostream>

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
        right = left = parent = nullptr;
    }
};

class CardBST {
public:
    CardBST();
    ~CardBST();
    void printInOrder();
    void printInOrder(Node* n);
    void clear(Node *n);
    void printPredecessor(int val1, int val2);
    void printSuccessor(int val1, int val2);
    void removeNode(int val1, int val2);
    Node* remove(int val1, int val2, Node* n);
    bool has(int val1, int val2);
    bool insert(int val1, int val2);
    bool insert(int val1, int val2, Node*& n);
    Node* getMin() {
        return min(root);
    };
    Node* getMax() {
        return max(root);
    };
    Node* successor(int val1, int val2);
    Node* successor(int val1, int val2, Node* n);
    Node* predecessor(int val1, int val2);
    Node* predecessor(int val1, int val2, Node* n);
    Node* getNode(int val1, int val2, Node* n);
    string suitToString (int suitValue);
    string valToString (int valueNum);


private:
    Node* root;
    Node* min(Node *n);
    Node* max(Node *n);
    bool nodeFinder(int val1, int val2, Node* n);
};

class Card{
    public:
    int suit;
    int value;
    Card(int suitNum = 0, int valueNum = 0) : suit(suitNum), value(valueNum) {}
    
    bool operator==(const Card& other) const {
        return (suit == other.suit) && (value == other.value);
    }
    bool operator<(const Card& other) const {
        if (suit == other.suit) {
            return value < other.value;
        }
        return suit < other.suit;
    }
    bool operator>(const Card& other) const {
        if (suit == other.suit) {
            return value > other.value;
        }
        return suit > other.suit;
    }
    bool operator<=(const Card& other) const {
        return (value < other.value) || (value == other.value && suit <= other.suit);
    }
    bool operator>=(const Card& other) const {
        return (value > other.value) || (value == other.value && suit >= other.suit);
    }
};
