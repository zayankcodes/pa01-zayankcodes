#include "card.h"
#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <string>

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cout << "Please provide 2 file names\n";
        return 1;
    }
    std::ifstream f1(argv[1]), f2(argv[2]);
    if (f1.fail() || f2.fail()) {
        std::cout << "Could not open file "
                  << (f1.fail() ? argv[1] : argv[2])
                  << "\n";
        return 1;
    }

    std::set<Card> alice, bob;
    std::string line;
    char sc; std::string vs;

    while (std::getline(f1, line) && !line.empty()) {
        std::istringstream iss(line);
        iss >> sc >> vs;
        alice.insert(Card::fromChars(sc, vs));
    }
    f1.close();

    while (std::getline(f2, line) && !line.empty()) {
        std::istringstream iss(line);
        iss >> sc >> vs;
        bob.insert(Card::fromChars(sc, vs));
    }
    f2.close();

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
        for (auto it = bob.rbegin(); it != bob.rend(); ++it) {
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


