// cards.cpp
// Author: John Hagedorn
// Implementation of the functions for the CardBST class

#include "cards.h"
#include <iostream>

using namespace std;

CardBST::CardBST() : root(nullptr) {}       // constructor function

CardBST::~CardBST() {                       // destructor function
    clearNode(root);
}

bool CardBST::insert(int val1, int val2) {  // insert function
    return insert(val1, val2, root);
}

bool CardBST::find(int val1, int val2) {     // function to find
    return findNode(val1, val2, root);
}

void CardBST::removeNode(int val1, int val2) {      // remove function
    root = remove(val1, val2, root);
}

Node* CardBST::succ(int val1, int val2) {
    Node* node = getNode(val1, val2, root);
    if (!node) return nullptr;

    if (node->right) {  // If node has right subtree, find min in subtree
        return min(node->right);
    }

    Node* successor = nullptr;  // else find nearest node for given node in the left subtree
    Node* current = root;

    while (current) {
        if (val1 < current->suit || (val1 == current->suit && val2 < current->value)) {
            successor = current;
            current = current->left;
        } else if (val1 > current->suit || (val1 == current->suit && val2 > current->value)) {
            current = current->right;
        } else {
            break; // found node
        }
    }

    return successor;
}

Node* CardBST::pred(int val1, int val2) {
    Node* node = getNode(val1, val2, root);
    if (!node) return nullptr;

    if (node->left) {       // If node has left subtree, find max in subtree
        return max(node->left);
    }

    Node* predecessor = nullptr;    // else find nearest node for given node in the right subtree
    Node* current = root;

    while (current) {
        if (val1 < current->suit || (val1 == current->suit && val2 < current->value)) {
            current = current->left;
        } else if (val1 > current->suit || (val1 == current->suit && val2 > current->value)) {
            predecessor = current;
            current = current->right;
        } else {
            break; // found node
        }
    }

    return predecessor;
}

void CardBST::printInOrder() {  // printInOrder function
    printInOrder(root);
}

void CardBST::printInOrder(Node* n) {   // printInOrder helper function
    if (n) {
        printInOrder(n->left);
        cout << suitToString(n->suit) << " " << valToString(n->value) << " ";
        printInOrder(n->right);
    }
}

string CardBST::suitToString(int suitValue) {   // function converts card suit to string
    switch (suitValue) {
        case 1:
            return "c";
        case 2:
            return "d";
        case 3:
            return "s";
        case 4:
            return "h";
        default:
            return "";
    }
}

string CardBST::valToString(int valueNum) {     // function converts card value to string
    switch (valueNum) {
        case 1:
            return "a";
        case 11:
            return "j";
        case 12:
            return "q";
        case 13:
            return "k";
        default:
            return to_string(valueNum);
    }
}

void CardBST::clearNode(Node* n) {              // function to clear given node
    if (n) {
        clearNode(n->left);
        clearNode(n->right);
        delete n;
    }
}

void CardBST::printPred(int val1, int val2) {    // cout predecessor function
    Node* pred1 = pred(val1, val2);
    if (pred1) {
        cout << "Predecessor: " << suitToString(pred1->suit) << " " << valToString(pred1->value) << endl;
    } else {
        cout << "No predecessor found." << endl;
    }
}

void CardBST::printSucc(int val1, int val2) {      // cout successor function
    Node* succ1 = succ(val1, val2);
    if (succ1) {
        cout << "Successor: " << suitToString(succ1->suit) << " " << valToString(succ1->value) << endl;
    } else {
        cout << "No successor found." << endl;
    }
}

Node* CardBST::getNode(int val1, int val2, Node* n) {    // function gets node given val
    if (!n) {
        return nullptr;
    }

    if (val1 < n->suit || (val1 == n->suit && val2 < n->value)) {
        return getNode(val1, val2, n->left);
    } else if (val1 > n->suit || (val1 == n->suit && val2 > n->value)) {
        return getNode(val1, val2, n->right);
    } else {
        return n;
    }
}

Node* CardBST::min(Node* n) {           // function finds min node
    while (n && n->left) {
        n = n->left;
    }
    return n;
}

Node* CardBST::max(Node* n) {           // function finds max node
    while (n && n->right) {
        n = n->right;
    }
    return n;
}

bool CardBST::insert(int val1, int val2, Node* n) {     // insert helper function
    if (!n) {
        root = new Node(val1, val2);
        return true;
    }

    if (val1 < n->suit || (val1 == n->suit && val2 < n->value)) {
        if (n->left) {
            return insert(val1, val2, n->left);
        } else {
            n->left = new Node(val1, val2);
            n->left->parent = n;
            return true;
        }
    } else if (val1 > n->suit || (val1 == n->suit && val2 > n->value)) {
        if (n->right) {
            return insert(val1, val2, n->right);
        } else {
            n->right = new Node(val1, val2);
            n->right->parent = n;
            return true;
        }
    } else {
        return false; // duplicate
    }
}

bool CardBST::findNode(int val1, int val2, Node* n) {   // helper function for has
    if (!n) {
        return false;
    }

    if (val1 < n->suit || (val1 == n->suit && val2 < n->value)) {
        return findNode(val1, val2, n->left);
    } else if (val1 > n->suit || (val1 == n->suit && val2 > n->value)) {
        return findNode(val1, val2, n->right);
    } else {
        return true; // found
    }
}

Node* CardBST::remove(int val1, int val2, Node* n) {    // remove helper function
    if (!n) {
        return nullptr;
    }

    if (val1 < n->suit || (val1 == n->suit && val2 < n->value)) {
        n->left = remove(val1, val2, n->left);
    } else if (val1 > n->suit || (val1 == n->suit && val2 > n->value)) {
        n->right = remove(val1, val2, n->right);
    } else {
        if (!n->left) {
            Node* temp = n->right;
            delete n;
            return temp;
        } else if (!n->right) {
            Node* temp = n->left;
            delete n;
            return temp;
        }

        Node* temp = min(n->right);
        n->suit = temp->suit;
        n->value = temp->value;
        n->right = remove(temp->suit, temp->value, n->right);
    }

    return n;
}
