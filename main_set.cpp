#include "card.h"
#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <string>

int main(int argc, char** argv) {
    std::set<Card> alice, bob;
    char sc;
    std::string vs;

    if (argc >= 3) {
        std::ifstream f1(argv[1]), f2(argv[2]);
        if (f1.fail() || f2.fail()) {
            std::cout << "Could not open file "
                      << (f1.fail() ? argv[1] : argv[2])
                      << "\n";
            return 1;
        }
        while (f1 >> sc >> vs) {
            alice.insert(Card::fromChars(sc, vs));
        }
        while (f2 >> sc >> vs) {
            bob.insert(Card::fromChars(sc, vs));
        }
    } else {
        bool second = false;
        std::string line;
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
    }

    while (true) {
        auto ait = alice.end();
        for (auto it = alice.begin(); it != alice.end(); ++it) {
            if (bob.count(*it)) { ait = it; break; }
        }
        if (ait == alice.end()) break;
        Card c = *ait;
        std::cout << "Alice picked matching card " << c.toString() << "\n";
        alice.erase(c);
        bob.erase(c);

        auto bit = bob.rend();
        for (auto it = bob.rbegin(); it != bob.rend(); --it) {
            if (alice.count(*it)) { bit = it; break; }
        }
        if (bit == bob.rend()) break;
        c = *bit;
        std::cout << "Bob picked matching card " << c.toString() << "\n";
        alice.erase(c);
        bob.erase(c);
    }

    std::cout << "\nAlice's cards:\n";
    for (auto& c : alice) {
        std::cout << c.toString() << "\n";
    }

    std::cout << "\nBob's cards:\n";
    for (auto& c : bob) {
        std::cout << c.toString() << "\n";
    }

    return 0;
}
