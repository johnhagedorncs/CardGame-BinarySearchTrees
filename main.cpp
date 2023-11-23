#include <iostream>
#include <fstream>
#include <vector>
#include "cards.h"

#include <iostream>
#include <fstream>
#include <vector>
#include "cards.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <alice_file> <bob_file>" << std::endl;
        return 1;
    }

    // Read cards into binary search trees for Alice and Bob
    BST aliceTree;
    BST bobTree;

    std::ifstream aliceFile(argv[1]);
    std::ifstream bobFile(argv[2]);

    if (!aliceFile || !bobFile) {
        std::cerr << "Error: Could not open input files." << std::endl;
        return 1;
    }

    readCards(aliceFile, aliceTree);
    readCards(bobFile, bobTree);

    aliceFile.close();
    bobFile.close();

    // Convert the binary search trees to vectors for efficient traversal
    std::vector<Card> aliceRemaining = aliceTree.inOrderTraversal();
    std::vector<Card> bobRemaining = bobTree.inOrderTraversal();

    // Game loop
    std::vector<std::pair<Card, Card>> matchingPairs;

    while (!aliceRemaining.empty() && !bobRemaining.empty()) {
        Card aliceCard = aliceRemaining.front();
        Card bobCard = bobRemaining.front();

        if (aliceCard == bobCard) {
            // Matching pair found
            matchingPairs.push_back({aliceCard, bobCard});

            // Remove matching cards from both hands
            aliceRemaining.erase(aliceRemaining.begin());
            bobRemaining.erase(bobRemaining.begin());
        } else if (aliceCard < bobCard) {
            // Alice's card is smaller, remove from her hand
            aliceRemaining.erase(aliceRemaining.begin());
        } else {
            // Bob's card is smaller, remove from his hand
            bobRemaining.erase(bobRemaining.begin());
        }
    }

    // Print matching pairs
    for (const auto &pair : matchingPairs) {
        std::cout << "Alice picked matching card " << pair.first << std::endl;
        std::cout << "Bob picked matching card " << pair.second << std::endl;
    }

    // Print remaining cards for both players after the game ends
    std::cout << "Alice's cards:" << std::endl;
    for (const auto &c : aliceRemaining) {
        std::cout << c << std::endl;
    }

    std::cout << "Bob's cards:" << std::endl;
    for (const auto &c : bobRemaining) {
        std::cout << c << std::endl;
    }

    return 0;
}

/*
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

    // Print remaining cards for Alice without duplicates
    cout << "Alice's cards:" << endl;
    list<Card> aliceRemaining;
    for (const auto& card : Alice.inOrderTraversal()) {
        bool duplicate = false;
        for (const auto& existingCard : aliceRemaining) {
            if (existingCard == card) {
                duplicate = true;
                break;
            }
        }
        if (!duplicate) {
            aliceRemaining.push_back(card);
        }
    }
    for (const auto& card : aliceRemaining) {
        cout << sToString(card.suit) << " " << vToString(card.value) << endl;
    }

    // Print remaining cards for Bob without duplicates
    cout << "Bob's cards:" << endl;
    list<Card> bobRemaining;
    for (const auto& card : Bob.inOrderTraversal()) {
        bool duplicate = false;
        for (const auto& existingCard : bobRemaining) {
            if (existingCard == card) {
                duplicate = true;
                break;
            }
        }
        if (!duplicate) {
            bobRemaining.push_back(card);
        }
    }
    for (const auto& card : bobRemaining) {
        cout << sToString(card.suit) << " " << vToString(card.value) << endl;
    }

    return 0;
}
*/