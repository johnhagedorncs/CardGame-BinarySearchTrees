// main.cpp
// Author: John Hagedorn

#include <iostream>
#include <fstream>
#include <string>
#include "utility.h"
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

void startGame(CardBST& Alice, CardBST& Bob) {
    Node* AliceNode = Alice.getMin();
    Node* BobNode = Bob.getMax();

    while (true) {
        bool found = false;

        if (AliceNode == nullptr || BobNode == nullptr) {
            break;
        }

        // Alice's turn
        while (AliceNode) {
            if (Bob.find(AliceNode->suit, AliceNode->value)) {
                found = true;
                int suit = AliceNode->suit;
                int value = AliceNode->value;
                Alice.removeNode(suit, value);
                Bob.removeNode(suit, value);
                cout << "Alice picked matching card " << Alice.suitToString(suit) << " " << Alice.valToString(value) << endl;
                AliceNode = Alice.succ(suit, value);
                break;
            } else {
                AliceNode = Alice.succ(AliceNode->suit, AliceNode->value);
            }
        }

        AliceNode = Alice.getMin();  // Reset AliceNode for the next iteration

        // Bob's turn
        while (BobNode) {
            if (Alice.find(BobNode->suit, BobNode->value)) {
                found = true;
                int suit = BobNode->suit;
                int value = BobNode->value;
                Alice.removeNode(suit, value);
                Bob.removeNode(suit, value);
                cout << "Bob picked matching card " << Bob.suitToString(suit) << " " << Bob.valToString(value) << endl;
                BobNode = Bob.pred(suit, value);
                break;
            } else {
                BobNode = Bob.pred(BobNode->suit, BobNode->value);
            }
        }

        BobNode = Bob.getMax();

        // If no matching cards were found for both players, end loop
        if (!found) {
            cout << endl;
            break;
        }
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
        int a1 = firstSet(line.substr(0, 1));
        int a2 = secondSet(line.substr(2, (line.length() == 4) ? 2 : 1));
        Alice.insert(a1, a2);
    }
    cardFile1.close();

    while (getline(cardFile2, line) && (line.length() > 0)) {
        int b1 = firstSet(line.substr(0, 1));
        int b2 = secondSet(line.substr(2, (line.length() == 4) ? 2 : 1));
        Bob.insert(b1, b2);
    }
    cardFile2.close();

    startGame(Alice, Bob);

    cout << "Alice's cards:" << endl;
    Alice.printInOrder();

    cout << endl << "Bob's cards:" << endl;
    Bob.printInOrder();

    return 0;
}