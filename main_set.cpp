#include "card.h"
#include <iostream>
#include <set>
#include <sstream>
#include <string>

int main() {
    std::set<Card> alice, bob;
    std::string line;
    bool second = false;
    char sc;
    std::string vs;

    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            second = true;
            continue;
        }
        std::istringstream iss(line);
        iss >> sc >> vs;
        if (!second)
            alice.insert(Card::fromChars(sc, vs));
        else
            bob.insert(Card::fromChars(sc, vs));
    }

    while (true) {
        auto ait = alice.end();
        for (auto it = alice.begin(); it != alice.end(); ++it) {
            if (bob.count(*it)) {
                ait = it;
                break;
            }
        }
        if (ait == alice.end()) break;
        Card c = *ait;
        std::cout << "Alice picked matching card " << c.toString() << "\n";
        alice.erase(c);
        bob.erase(c);

        auto bit = bob.rend();
        for (auto it = bob.rbegin(); it != bob.rend(); --it) {
            if (alice.count(*it)) {
                bit = it;
                break;
            }
        }
        if (bit == bob.rend()) break;
        c = *bit;
        std::cout << "Bob picked matching card " << c.toString() << "\n";
        alice.erase(c);
        bob.erase(c);
    }

    std::cout << "\nAlice's cards:\n";
    for (auto& c : alice) std::cout << c.toString() << "\n";
    std::cout << "\nBob's cards:\n";
    for (auto& c : bob)   std::cout << c.toString() << "\n";

    return 0;
}
