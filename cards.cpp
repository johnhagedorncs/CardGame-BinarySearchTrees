// cards.cpp
// Author: John Hagedorn
// Implementation of the classes defined in cards.h

#include "cards.h"
#include "utility.h"
#include <iostream>
#include <vector>
using namespace std;

Card::Card(string suit, string value){
    cardSuit = suit;
    cardValue = value;
}

Card::Card(int suit, int value) {
    cardSuit = CardUtility::suitToString(suit);
    cardValue = CardUtility::valToString(value);
}

string Card::get_value() const {
    return cardValue;
}

string Card::get_suit() const {
    return cardSuit;
}

bool Card::operator==(const Card& other) const {
    return (cardValue == other.cardValue) && (cardSuit == other.cardSuit);
    // overloads the == operator to check if card val AND suit are equal to 'other'
}

bool Card::operator>(const Card& other) const {
    if (cardSuit != other.cardSuit) {
        if (cardSuit == "Clubs") {               // lowest suit
            return false;                        // other.card wins
        } else if (other.cardSuit == "Clubs") {
            return true;                         // card wins
        } else if (cardSuit == "Diamonds") {
            return false; 
        } else if (other.cardSuit == "Diamonds") {
            return true; 
        } else if (cardSuit == "Spades") {
            return false; 
        } else if (other.cardSuit == "Spades") {
            return true;
        } else {                                   // hearts
            return false; // Other card has a greater suit
        }
    } else {
        // If suits are same, compare based on value
        return (cardValue > other.cardValue);
    }
}

bool Card::operator<(const Card& other) const {
    if (cardSuit != other.cardSuit) {
        if (cardSuit == "Clubs") {               // lowest suit
            return true;                         // card wins
        } else if (other.cardSuit == "Clubs") {
            return false;                        // other.card wins
        } else if (cardSuit == "Diamonds") {
            return true; 
        } else if (other.cardSuit == "Diamonds") {
            return false; 
        } else if (cardSuit == "Spades") {
            return true; 
        } else if (other.cardSuit == "Spades") {
            return false;
        } else {                                   // hearts
            return true; // Card has a greater suit
        }
    } else {
        // If suits are the same, compare based on value
        return (cardValue < other.cardValue);
    }
}



BinarySearchTree::BinarySearchTree() {      //constructor
    root = nullptr;
}

BinarySearchTree::~BinarySearchTree() {     //destructor
    clear(root);
}

void BinarySearchTree::clear(Node *n) {
    if (n == nullptr) {
        return;
    } else {
        clear(n->left);
        clear(n->right);
        delete n;
    }
}

void BinarySearchTree::insert(const Card& card) {
    insert(root, card);
}

void BinarySearchTree::insert(Node*& node, const Card& card) {  // insert helper function
    if (node == nullptr) {
        node = new Node(card);
        return;
    } else if (card < node->data) {
        insert(node->left, card);
    } else {
        insert(node->right, card);
    }
}

void BinarySearchTree::remove(const Card& card) {
    remove(root, card);
}

void BinarySearchTree::remove(Node*& node, const Card& card) {  //remove helper function
    if (node == NULL) {
        return;
    }
    if (card < node->data) {
        remove(node->left, card);
    } else if (card > node->data) {
        remove(node->right, card);
    } else {
        if (node->left == NULL && node->right == NULL) {     // Node has no children
            delete node;
            node = NULL;
        } else if (node->left == NULL) {                     // Node has one right child
            Node* temp = node;
            node = node->right;
            delete temp;
        } else if (node->right == NULL) {                    // Node has one left child
            Node* temp = node;
            node = node->left;
            delete temp;
        } else {                                             // Node has two children
            Node* successor = node->right;                   // Find the successor
            while (successor->left != NULL) {
                successor = successor->left;
            }
            node->data = successor->data;                    // Copy successor data to current node
            remove(node->right, successor->data);            // remove successor from right subtree
        }
    }
}

bool BinarySearchTree::find(const Card& card) const {
    return find(root, card);
}

bool BinarySearchTree::find(Node* node, const Card& card) const {
    if (node == NULL) {
        return false;
    }
    if (card == node->data) {
        return true;  
    } else if (card < node->data) {
        return find(node->left, card);
    } else {
        return find(node->right, card);
    }
}

bool BinarySearchTree::isEmpty() const {
    return (root == nullptr);
}

BinarySearchTree::Node* BinarySearchTree::predecessorNode(const Card& card) const{
    Node* predecessorNode = nullptr;
    Node* current = root;
    while (current != nullptr) {
        if (card == current->data) {
            if (current->left != nullptr) {
                current = current->left;
                while (current->right != nullptr) {
                    current = current->right;
                }
                predecessorNode = current;
            }
            break;
        } else if (card < current->data) {
            current = current->left;
        } else {
            predecessorNode = current;
            current = current->right;
        }
    }
    return predecessorNode;
}

// returns the predecessor value of the given value or 0 if there is none
Card BinarySearchTree::predecessor(const Card& card) const {
    Node* preNode = predecessorNode(card);
    if (preNode != nullptr) {
        return preNode->data;
    } else {
        return Card("",  "");
    }
}

// returns the Node containing the successor of the given value
BinarySearchTree::Node* BinarySearchTree::successorNode(const Card& card) const{
    Node* curr = root;
    Node* successor = nullptr;
    while (curr != nullptr) {
        if (card < curr->data) {
            successor = curr;
            curr = curr->left;
        } else if (card > curr->data) {
            curr = curr->right;
        } else {
            if (curr->right != nullptr) {
                successor = curr->right;
                while (successor->left != nullptr) {
                    successor = successor->left;
                }
            }
            break;
        }
    }
    return successor;
}
// returns the successor value of the given value or 0 if there is none
Card BinarySearchTree::successor(const Card& card) const {
    Node* successNode = successorNode(card);
    if (successNode != nullptr) {
        return successNode->data;
    } else {
        return Card("",  "");
    }
}

void BinarySearchTree::printInOrder() const {
    printInOrder(root, "");
}

void BinarySearchTree::printInOrder(Node* n) const {
    if (n != nullptr) {
        printInOrder(n->left);
        cout << n->data.get_suit() << " " << n->data.get_value() << endl;
        printInOrder(n->right);
    }
}

void BinarySearchTree::printInOrder(const string& player) const {
    printInOrder(root, player);
}

void BinarySearchTree::printInOrder(Node* n, const string& player) const {
    if (n != nullptr) {
        printInOrder(n->left, player);

        if (!player.empty()) {
            cout << player << "'s picked matching card " << n->data.get_suit() << " " << n->data.get_value() << endl;
        }

        printInOrder(n->right, player);
    }
}

string BinarySearchTree::valToString(int value) {
    if (value >= 2 && value <= 10) {
        return to_string(value);
    } else {
        switch (value) {
            case 1: return "Ace";
            case 11: return "Jack";
            case 12: return "Queen";
            case 13: return "King";
            default: return "Unknown";
        }
    }
}
    
string BinarySearchTree::suitToString(int suit) {
    switch (suit) {
        case 0: return "Clubs";
        case 1: return "Diamonds";
        case 2: return "Spades";
        case 3: return "Hearts";
        default: return "Unknown";
    }
}

BinarySearchTree::Node* BinarySearchTree::getMin() const {
    Node* current = root;
    while (current != nullptr && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

BinarySearchTree::Node* BinarySearchTree::getMax() const {
    Node* current = root;
    while (current != nullptr && current->right != nullptr) {
        current = current->right;
    }
    return current;
}

bool BinarySearchTree::has(int suit, int value) {
    return find(Card(suitToString(suit), valToString(value)));
}

void BinarySearchTree::remove(int suit, int value) {
    remove(root, Card(suitToString(suit), valToString(value)));
}

BinarySearchTree::Node* BinarySearchTree::successor(int suit, int value) {
    return successorNode(Card(suitToString(suit), valToString(value)));
}

BinarySearchTree::Node* BinarySearchTree::predecessor(int suit, int value) {
    return predecessorNode(Card(suitToString(suit), valToString(value)));
}
