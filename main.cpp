// main.cpp
// Author: John Hagedorn

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "cards.h"

using namespace std;

int firstSet(string s1) {
    if (s1 == "c") {
        return 1;
    } else if (s1 == "d") {
        return 2;
    } else if (s1 == "s") {
        return 3;
    } else {
        return 4;
    }
}

int secondSet(string s2) {
    if (s2 == "a") {
        return 1;
    } else if (s2 == "j") {
        return 11;
    } else if (s2 == "q") {
        return 12;
    } else if (s2 == "k") {
        return 13;
    } else {
        return stoi(s2);
    }
}

string vToString(int valueNum) {
    if (valueNum == 1) {
        return "a";
    } else if (valueNum == 11) {
        return "j";
    } else if (valueNum == 12) {
        return "q";
    } else if (valueNum == 13) {
        return "k";
    } else {
        return to_string(valueNum);
    }
}

string sToString(int suitValue) {
    if (suitValue == 1) {
        return "c";
    } else if (suitValue == 2) {
        return "d";
    } else if (suitValue == 3) {
        return "s";
    } else {
        return "h";
    }
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

    CardBST Alice;
    CardBST Bob;

    // Read each file
    while (getline(cardFile1, line) && (line.length() > 0)) {
        int a1;
        int a2;
        string strng1 = line.substr(0, 1);
        string strng2;
        if (line.length() == 4) {
            strng2 = line.substr(2, 2);
        } else {
            strng2 = line.substr(2, 1);
        }
        a1 = firstSet(strng1);
        a2 = secondSet(strng2);
        Alice.insert(a1, a2);
    }
    cardFile1.close();

    while (getline(cardFile2, line) && (line.length() > 0)) {
        int b1;
        int b2;
        string strng1 = line.substr(0, 1);
        string strng2;
        if (line.length() == 4) {
            strng2 = line.substr(2, 2);
        } else {
            strng2 = line.substr(2, 1);
        }
        b1 = firstSet(strng1);
        b2 = secondSet(strng2);
        Bob.insert(b1, b2);
    }
    cardFile2.close();

    Node* AliceNode = Alice.getMin();
    Node* BobNode = Bob.getMax();

    while (true) {
    bool aliceFound = false;
    bool bobFound = false;

    if (AliceNode == nullptr || BobNode == nullptr) {
        break;
    }

    // Alice's turn
    while (AliceNode) {
        if (Bob.has(AliceNode->suit, AliceNode->value)) {
            aliceFound = true;
            int suit = AliceNode->suit;
            int value = AliceNode->value;
            Alice.removeNode(suit, value);
            Bob.removeNode(suit, value);
            cout << "Alice picked matching card " << sToString(suit) << " " << vToString(value) << endl;

            // Update Alice's node after removal
            AliceNode = Alice.successor(suit, value);

            break;
        } else {
            AliceNode = Alice.successor(AliceNode->suit, AliceNode->value);
        }
    }

    AliceNode = Alice.getMin();  // Reset AliceNode for the next iteration

    // Bob's turn
    while (BobNode) {
        if (Alice.has(BobNode->suit, BobNode->value)) {
            bobFound = true;
            int suit = BobNode->suit;
            int value = BobNode->value;
            Alice.removeNode(suit, value);
            Bob.removeNode(suit, value);
            cout << "Bob picked matching card " << sToString(suit) << " " << vToString(value) << endl;

            // Update Bob's node after removal
            BobNode = Bob.predecessor(suit, value);

            break;
        } else {
            BobNode = Bob.predecessor(BobNode->suit, BobNode->value);
        }
    }

    BobNode = Bob.getMax();

    // If no matching cards were found for both players, exit the loop
    if (!aliceFound && !bobFound) {
        break;
    }
}


    cout << "Alice's cards:" << endl;
    Alice.printInOrder();

    cout << "Bob's cards:" << endl;
    Bob.printInOrder();

    return 0;
}