// main.cpp
#include <iostream>
#include <fstream>
#include <string>
#include "cards.h"
#include "utility.h"

using namespace std;

int main(int argv, char** argc){
  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  
  ifstream cardFile1 (argc[1]);
  ifstream cardFile2 (argc[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argc[2];
    return 1;
  }
  
  //Read each file
  while (getline (cardFile1, line) && (line.length() > 0)){

  }
  cardFile1.close();


  while (getline (cardFile2, line) && (line.length() > 0)){

  }
  cardFile2.close();
  
/*

  BinarySearchTree aliceCards, bobCards;

    while (getline(cardFile1, line) && (line.length() > 0)) {   // Read Alice's cards
        Card card("Alice", line);
        aliceCards.insert(card);
    }
    cardFile1.close();

    while (getline(cardFile2, line) && (line.length() > 0)) {   // Read Bob's cards
        Card card("Bob", line);
        bobCards.insert(card);
    }
    cardFile2.close();

    BinarySearchTree::Node* aliceNode = aliceCards.getRoot("");  // Iterate through Alice's cards to find and remove matching pairs in Bob's cards
    while (aliceNode != nullptr) {                                     // Start from smallest card
        Card aliceCard = aliceNode->data;

        if (bobCards.find(aliceCard)) {                       // Matching pair found, remove from both hands
            aliceCards.remove(aliceCard);
            bobCards.remove(aliceCard);
        }

        aliceNode = aliceCards.successorNode(aliceCard);      // Move to next card in Alice's hand
    }

    cout << "Remaining cards in Alice's hand:" << endl;       // Print remaining cards in Alice's hand
    aliceCards.printInOrder();

    cout << "\nRemaining cards in Bob's hand:" << endl;       // Print remaining cards in Bob's hand
    bobCards.printInOrder();

  */
    
    return 0;
}
