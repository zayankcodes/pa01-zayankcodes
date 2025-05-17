#include "card.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <vector>

int main(int argc, char** argv) {
    std::vector<Card> v1, v2;
    if (argc < 3) {
        std::string line;
        bool second = false;
        while (std::getline(std::cin, line)) {
            if (line.empty()) { second = true; continue; }
            std::istringstream iss(line);
            char sc; std::string vs;
            iss >> sc >> vs;
            if (!second) v1.push_back(Card::fromChars(sc, vs));
            else         v2.push_back(Card::fromChars(sc, vs));
        }
    } else {
        std::ifstream f1(argv[1]), f2(argv[2]);
        std::string line;
        while (std::getline(f1, line) && !line.empty()) {
            std::istringstream iss(line);
            char sc; std::string vs;
            iss >> sc >> vs;
            v1.push_back(Card::fromChars(sc, vs));
        }
        while (std::getline(f2, line) && !line.empty()) {
            std::istringstream iss(line);
            char sc; std::string vs;
            iss >> sc >> vs;
            v2.push_back(Card::fromChars(sc, vs));
        }
    }
    std::set<Card> alice(v1.begin(), v1.end());
    std::set<Card> bob(v2.begin(), v2.end());

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
    for (auto& c : alice) std::cout << c.toString() << "\n";
    std::cout << "\nBob's cards:\n";
    for (auto& c : bob)   std::cout << c.toString() << "\n";

    return 0;
}
