// cards.cpp
// Author: John Hagedorn
// Implementation of the CardBST class

#include "cards.h"
#include <iostream>

using namespace std;

// Constructor
CardBST::CardBST() : root(nullptr) {}

// Destructor
CardBST::~CardBST() {
    clear(root);
}

// Function to print the cards in order
void CardBST::printInOrder() {
    printInOrder(root);
}

// Function to clear the tree
void CardBST::clear(Node* n) {
    if (n != nullptr) {
        clear(n->left);
        clear(n->right);
        delete n;
    }
}

// Function to print the predecessor of a card in the BST
void CardBST::printPredecessor(int val1, int val2) {
    Node* predecessor = this->predecessor(val1, val2);
    if (predecessor != nullptr) {
        cout << "Predecessor: " << suitToString(predecessor->suit) << " " << valToString(predecessor->value) << endl;
    } else {
        cout << "No predecessor found." << endl;
    }
}

// Function to print the successor of a card in the BST
void CardBST::printSuccessor(int val1, int val2) {
    Node* successor = this->successor(val1, val2);
    if (successor != nullptr) {
        cout << "Successor: " << suitToString(successor->suit) << " " << valToString(successor->value) << endl;
    } else {
        cout << "No successor found." << endl;
    }
}

// Function to remove a card from the BST
void CardBST::removeNode(int val1, int val2) {
    root = remove(val1, val2, root);
}

// Function to check if a card is present in the BST
bool CardBST::has(int val1, int val2) {
    return nodeFinder(val1, val2, root);
}

// Function to get the successor of a card in the BST
Node* CardBST::successor(int val1, int val2) {
    return successor(val1, val2, root);
}

// Function to get the predecessor of a card in the BST
Node* CardBST::predecessor(int val1, int val2) {
    return predecessor(val1, val2, root);
}

// Recursive helper function to find the successor of a card in the BST
Node* CardBST::successor(int val1, int val2, Node* n) {
    if (n == nullptr) {
        return nullptr;
    }

    Card currentCard(n->suit, n->value);
    Card targetCard(val1, val2);

    if (currentCard <= targetCard) {
        return successor(val1, val2, n->right);
    } else {
        Node* successorNode = successor(val1, val2, n->left);
        return (successorNode != nullptr) ? successorNode : n;
    }
}

// Recursive helper function to find the predecessor of a card in the BST
Node* CardBST::predecessor(int val1, int val2, Node* n) {
    if (n == nullptr) {
        return nullptr;
    }

    Card currentCard(n->suit, n->value);
    Card targetCard(val1, val2);

    if (currentCard >= targetCard) {
        return predecessor(val1, val2, n->left);
    } else {
        Node* predecessorNode = predecessor(val1, val2, n->right);
        return (predecessorNode != nullptr) ? predecessorNode : n;
    }
}

// Function to get a specific node in the BST
Node* CardBST::getNode(int val1, int val2, Node* n) {
    if (n == nullptr) {
        return nullptr;
    }

    Card currentCard(n->suit, n->value);
    Card targetCard(val1, val2);

    if (currentCard == targetCard) {
        return n;
    } else if (currentCard < targetCard) {
        return getNode(val1, val2, n->right);
    } else {
        return getNode(val1, val2, n->left);
    }
}

// Utility function to convert suit to string
string CardBST::suitToString(int suit) {
    switch (suit) {
        case 1: return "c";
        case 2: return "d";
        case 3: return "s";
        case 4: return "h";
        default: return "Unknown";
    }
}

// Utility function to convert value to string
string CardBST::valToString(int value) {
    if (value == 1) {
        return "a";
    } else if (value == 11) {
        return "j";
    } else if (value == 12) {
        return "q";
    } else if (value == 13) {
        return "k";
    } else {
        return to_string(value);
    }
}

// Recursive helper function to print the cards in order
void CardBST::printInOrder(Node* n) {
    if (n != nullptr) {
        printInOrder(n->left);
        cout << suitToString(n->suit) << " " << valToString(n->value) << endl;
        printInOrder(n->right);
    }
}

// Recursive helper function to remove a card from the BST
Node* CardBST::remove(int val1, int val2, Node* n) {
    if (n == nullptr) {
        return nullptr;
    }

    Card currentCard(n->suit, n->value);
    Card targetCard(val1, val2);

    if (currentCard < targetCard) {
        n->right = remove(val1, val2, n->right);
    } else if (currentCard > targetCard) {
        n->left = remove(val1, val2, n->left);
    } else {
        if (n->left == nullptr && n->right == nullptr) {
            // Case 1: No child
            delete n;
            return nullptr;
        } else if (n->left == nullptr) {
            // Case 2: One child (right)
            Node* temp = n->right;
            delete n;
            return temp;
        } else if (n->right == nullptr) {
            // Case 2: One child (left)
            Node* temp = n->left;
            delete n;
            return temp;
        } else {
            // Case 3: Two children
            Node* successor = min(n->right);
            n->suit = successor->suit;
            n->value = successor->value;
            n->right = remove(successor->suit, successor->value, n->right);
        }
    }
    return n;
}

// Recursive helper function to find the minimum value node in the BST
Node* CardBST::min(Node* n) {
    while (n->left != nullptr) {
        n = n->left;
    }
    return n;
}

// Recursive helper function to find the maximum value node in the BST
Node* CardBST::max(Node* n) {
    while (n->right != nullptr) {
        n = n->right;
    }
    return n;
}

bool CardBST::insert(int val1, int val2) {
    return insert(val1, val2, root);
}

bool CardBST::insert(int val1, int val2, Node*& n) {
    if (n == nullptr) {
        n = new Node(val1, val2);
        return true;
    }

    Card currentCard(n->suit, n->value);
    Card targetCard(val1, val2);

    if (currentCard < targetCard) {
        return insert(val1, val2, n->right);
    } else if (currentCard > targetCard) {
        return insert(val1, val2, n->left);
    } else {
        // Duplicate card found
        return false;
    }
}

// Recursive helper function to check if a card is present in the BST
bool CardBST::nodeFinder(int val1, int val2, Node* n) {
    if (n == nullptr) {
        return false;
    }

    Card currentCard(n->suit, n->value);
    Card targetCard(val1, val2);

    if (currentCard < targetCard) {
        return nodeFinder(val1, val2, n->right);
    } else if (currentCard > targetCard) {
        return nodeFinder(val1, val2, n->left);
    } else {
        return true;
    }
}
