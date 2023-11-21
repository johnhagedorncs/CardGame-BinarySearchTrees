// CardUtility.cpp
#include "utility.h"

std::string CardUtility::suitToString(int suit) {
    switch (suit) {
        case 0: return "Clubs";
        case 1: return "Diamonds";
        case 2: return "Spades";
        case 3: return "Hearts";
        default: return "Unknown";
    }
}

std::string CardUtility::valToString(int value) {
    if (value >= 2 && value <= 10) {
        return std::to_string(value);
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