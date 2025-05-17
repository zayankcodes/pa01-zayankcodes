#include "card.h"
#include "card_list.h"
#include <iostream>
#include <fstream>
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

    bst alice, bob;
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
            if (bob.contains(*it)) { ait = it; break; }
        }
        if (ait == alice.end()) break;
        std::cout << "Alice picked matching card " << ait->toString() << "\n";
        Card ac = *ait;
        alice.remove(ac);
        bob.remove(ac);

        auto bit = bob.rend();
        for (auto it = bob.rbegin(); it != bob.rend(); ++it) {
            if (alice.contains(*it)) { bit = it; break; }
        }
        if (bit == bob.rend()) break;
        std::cout << "Bob picked matching card " << bit->toString() << "\n";
        Card bc = *bit;
        alice.remove(bc);
        bob.remove(bc);
    }

    std::cout << "\nAlice's cards:\n";
    alice.printDeck();
    std::cout << "\nBob's cards:\n";
    bob.printDeck();

    return 0;
}
