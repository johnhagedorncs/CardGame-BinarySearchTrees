#include "cards.h"
#include <fstream>
#include <limits>

// Implementation for Card class
bool Card::operator==(const Card& other) const {
    return (suit == other.suit) && (value == other.value);
}

bool Card::operator<(const Card& other) const {
    if (suit != other.suit) {
        return suit < other.suit;
    }
    return value < other.value;
}

std::ostream& operator<<(std::ostream& os, const Card& card) {
    os << card.suit << " " << card.value;
    return os;
}

// Implementation for BST class
BST::Node::Node(const Card& card) : data(card), left(nullptr), right(nullptr) {}

BST::BST() : root(nullptr) {}

void BST::insert(const Card& card) {
    root = insertHelper(root, card);
}

BST::Node* BST::insertHelper(Node* node, const Card& card) {
    if (node == nullptr) {
        return new Node(card);
    }

    if (card < node->data) {
        node->left = insertHelper(node->left, card);
    } else {
        node->right = insertHelper(node->right, card);
    }

    return node;
}

std::vector<Card> BST::inOrderTraversal() const {
    std::vector<Card> result;
    inOrderTraversalHelper(root, result);
    return result;
}

void BST::inOrderTraversalHelper(Node* node, std::vector<Card>& result) const {
    if (node) {
        inOrderTraversalHelper(node->left, result);
        result.push_back(node->data);
        inOrderTraversalHelper(node->right, result);
    }
}

// Function to read cards from a file and insert them into a BST
void readCards(std::ifstream& file, BST& tree) {
    char suit;
    std::string value;

    while (file.get(suit) >> value) {
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line
        Card card{suit, value};
        tree.insert(card);
    }
}
/*
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
        // Node with only one child or no child
        if (n->left == nullptr) {
            Node* temp = n->right;
            delete n;
            return temp;
        } else if (n->right == nullptr) {
            Node* temp = n->left;
            delete n;
            return temp;
        }

        // Node with two children, get the inorder successor
        Node* successor = min(n->right);

        // Copy the inorder successor's data to this node
        n->suit = successor->suit;
        n->value = successor->value;

        // Delete the inorder successor
        n->right = remove(successor->suit, successor->value, n->right);
    }
    return n;
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

    Card targetCard(val1, val2);

    Node* successorNode = nullptr;
    while (n != nullptr) {
        Card currentCard(n->suit, n->value);

        if (currentCard <= targetCard) {
            n = n->right;
        } else {
            successorNode = n;
            n = n->left;
        }
    }

    return successorNode;
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

// Recursive helper function to insert a card into the BST
bool CardBST::insert(int val1, int val2, Node*& n) {
    if (n == nullptr) {
        n = new Node(val1, val2);
        return true;
    }

    Card currentCard(n->suit, n->value);
    Card targetCard(val1, val2);

    if (currentCard < targetCard) {
        if (n->right == nullptr) {
            n->right = new Node(val1, val2);
            n->right->parent = n;  // Update the parent pointer
            return true;
        } else {
            return insert(val1, val2, n->right);
        }
    } else if (currentCard > targetCard) {
        if (n->left == nullptr) {
            n->left = new Node(val1, val2);
            n->left->parent = n;  // Update the parent pointer
            return true;
        } else {
            return insert(val1, val2, n->left);
        }
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

vector<Card> CardBST::inOrderTraversal() {
    vector<Card> result;
    inOrderTraversal(root, result);
    return result;
}

void CardBST::inOrderTraversal(Node* n, vector<Card>& result) {
    if (n != nullptr) {
        inOrderTraversal(n->left, result);
        result.push_back(Card{n->suit, n->value});
        inOrderTraversal(n->right, result);
    }
}
*/