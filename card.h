#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>
#include <stdexcept>

enum class Suit { CLUBS, DIAMONDS, SPADES, HEARTS };

class Card {
public:
    Card();
    Card(Suit s, int r);
    static Card fromChars(char suitChar, const std::string& valueStr);
    std::string toString() const;
    bool operator<(const Card& other) const;
    bool operator==(const Card& other) const;
    bool operator!=(const Card& other) const;
private:
    Suit suit_;
    int  rank_;
};

std::ostream& operator<<(std::ostream& os, const Card& card);

#endif
