// CardUtility.h
#ifndef CARD_UTILITY_H
#define CARD_UTILITY_H

#include <string>

class CardUtility {
public:
    static std::string suitToString(int suit);
    static std::string valToString(int value);
};

#endif  // CARD_UTILITY_H