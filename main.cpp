#include "card.h"
#include "card_list.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

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
            if (!second) v1.emplace_back(Card::fromChars(sc, vs));
            else         v2.emplace_back(Card::fromChars(sc, vs));
        }
    } else {
        std::ifstream f1(argv[1]), f2(argv[2]);
        std::string line;
        while (std::getline(f1, line) && !line.empty()) {
            std::istringstream iss(line);
            char sc; std::string vs;
            iss >> sc >> vs;
            v1.emplace_back(Card::fromChars(sc, vs));
        }
        while (std::getline(f2, line) && !line.empty()) {
            std::istringstream iss(line);
            char sc; std::string vs;
            iss >> sc >> vs;
            v2.emplace_back(Card::fromChars(sc, vs));
        }
    }

    bst alice, bob;
    for (auto& c : v1) alice.insert(c);
    for (auto& c : v2) bob.insert(c);

    playGame(alice, bob);
    return 0;
}
