#include "card.h"
#include <sstream>
#include <cctype>

Card::Card(): suit_(Suit::CLUBS), rank_(1) {}
Card::Card(Suit s,int r): suit_(s), rank_(r) {}

Card Card::fromChars(char suitChar,const std::string& valueStr){
    Suit s;
    switch(std::tolower(suitChar)){
        case 'c': s=Suit::CLUBS; break;
        case 'd': s=Suit::DIAMONDS; break;
        case 's': s=Suit::SPADES; break;
        case 'h': s=Suit::HEARTS; break;
        default: throw std::invalid_argument("Invalid suit");
    }
    int r;
    if(valueStr=="a"||valueStr=="A") r=1;
    else if(valueStr=="j"||valueStr=="J") r=11;
    else if(valueStr=="q"||valueStr=="Q") r=12;
    else if(valueStr=="k"||valueStr=="K") r=13;
    else {
        std::istringstream iss(valueStr);
        if(!(iss>>r)||r<2||r>10) throw std::invalid_argument("Invalid rank");
    }
    return Card(s,r);
}

std::string Card::toString() const {
    char sc = (suit_==Suit::CLUBS?'c':suit_==Suit::DIAMONDS?'d':suit_==Suit::SPADES?'s':'h');
    std::string vs;
    switch(rank_){
        case 1: vs="a"; break;
        case 11: vs="j"; break;
        case 12: vs="q"; break;
        case 13: vs="k"; break;
        default: vs=std::to_string(rank_);
    }
    return std::string(1,sc)+" "+vs;
}

bool Card::operator<(const Card& o) const {
    auto ord=[&](Suit x){
        return x==Suit::CLUBS?0:
               x==Suit::DIAMONDS?1:
               x==Suit::SPADES?2:3;
    };
    if(suit_!=o.suit_) return ord(suit_)<ord(o.suit_);
    return rank_<o.rank_;
}

bool Card::operator==(const Card& o) const {
    return suit_==o.suit_&&rank_==o.rank_;
}
bool Card::operator!=(const Card& o) const {
    return !(*this==o);
}

std::ostream& operator<<(std::ostream& os,const Card& c){
    os<<c.toString();
    return os;
}
