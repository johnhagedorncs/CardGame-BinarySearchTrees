#include <iostream>
#include <fstream>
#include <string>
#include "cards.h"

using namespace std;

int firstSet(string s1) {
    int a;
    if (s1 == "c") {
        a = 1;
    } else if (s1 == "d") {
        a = 2;
    } else if (s1 == "s") {
        a = 3;
    } else {
        a = 4;
    }
    return a;
}

int secondSet(string s2) {
    int a;
    if (s2 == "a") {
        a = 1;
    } else if (s2 == "j") {
        a = 11;
    } else if (s2 == "q") {
        a = 12;
    } else if (s2 == "k") {
        a = 13;
    } else {
        a = stoi(s2);
    }
    return a;
}

int main(int argc, char** argv) {
    if (argc < 3) {
        cout << "Please provide 2 file names" << endl;
        return 1;
    }

    ifstream cardFile1(argv[1]);
    ifstream cardFile2(argv[2]);
    string line;

    if (cardFile1.fail() || cardFile2.fail()) {
        cout << "Could not open file " << argv[2];
        return 1;
    }

    BinarySearchTree Alice;
    BinarySearchTree Bob;

    // Read each file
    while (getline(cardFile1, line) && (line.length() > 0)) {
        int a1;
        int a2;
        string firstStr = line.substr(0, 1);
        string secondStr;
        if (line.length() == 4) {
            secondStr = line.substr(2, 2);
        } else {
            secondStr = line.substr(2, 1);
        }
        a1 = firstSet(firstStr);
        a2 = secondSet(secondStr);

        Card newCard = Card(CardUtility::suitToString(a1), CardUtility::valToString(a2));
        Alice.insert(newCard);
    }
    cardFile1.close();

    while (getline(cardFile2, line) && (line.length() > 0)) {
        int b1;
        int b2;
        string firstStr = line.substr(0, 1);
        string secondStr;
        if (line.length() == 4) {
            secondStr = line.substr(2, 2);
        } else {
            secondStr = line.substr(2, 1);
        }
        b1 = firstSet(firstStr);
        b2 = secondSet(secondStr);

        Card newCard = Card(CardUtility::suitToString(b1), CardUtility::valToString(b2));
        Bob.insert(newCard);
    }
    cardFile2.close();

    BinarySearchTree::Node* AliceNode = Alice.getMin();
    BinarySearchTree::Node* BobNode = Bob.getMax();

    while (true) {
        bool found = false;

        if (AliceNode == nullptr || BobNode == nullptr) {
            break;
        }

        while (AliceNode) {
            int aliceSuit = Alice.suitToInteger(AliceNode->data.get_suit());
            int aliceValue = Alice.valueToInteger(AliceNode->data.get_value());

            if (Bob.has(aliceSuit, aliceValue)) {
                found = true;

                Card cardToRemove(aliceSuit, aliceValue);
                Alice.remove(cardToRemove);
                Bob.remove(cardToRemove);

                cout << "Matching card found: " << AliceNode->data.get_suit() << " " << AliceNode->data.get_value() << endl;

                AliceNode = Alice.successor(aliceSuit, aliceValue);

                break;
            } else {
                AliceNode = Alice.successor(aliceSuit, aliceValue);
            }
        }

        AliceNode = Alice.getMin();  // Reset AliceNode for the next iteration

        // Bob's turn
        while (BobNode) {
            int bobSuit = Bob.suitToInteger(BobNode->data.get_suit());
            int bobValue = Bob.valueToInteger(BobNode->data.get_value());

            if (Alice.has(bobSuit, bobValue)) {
                found = true;

                Card cardToRemove(bobSuit, bobValue);
                Alice.remove(cardToRemove);
                Bob.remove(cardToRemove);

                cout << "Matching card found: " << BobNode->data.get_suit() << " " << BobNode->data.get_value() << endl;

                BobNode = Bob.predecessor(bobSuit, bobValue);

                break;
            } else {
                BobNode = Bob.predecessor(bobSuit, bobValue);
            }
        }

        BobNode = Bob.getMax();  // Reset BobNode for the next iteration
    }

    return 0;
}
