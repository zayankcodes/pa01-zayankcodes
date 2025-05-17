#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include "card.h"

using namespace std;

int main(int argv, char** argc){
    if(argv < 3){
        cout << "Please provide 2 file names" << endl;
        return 1;
    }

    ifstream cardFile1(argc[1]);
    ifstream cardFile2(argc[2]);
    if(cardFile1.fail() || cardFile2.fail()){
        cout << "Could not open file " << argc[2] << endl;
        return 1;
    }

    set<Card> alice, bob;
    string line;
    while(getline(cardFile1, line) && !line.empty()){
        istringstream iss(line);
        char sc; string vs;
        iss >> sc >> vs;
        alice.insert(Card::fromChars(sc, vs));
    }
    cardFile1.close();

    while(getline(cardFile2, line) && !line.empty()){
        istringstream iss(line);
        char sc; string vs;
        iss >> sc >> vs;
        bob.insert(Card::fromChars(sc, vs));
    }
    cardFile2.close();

    while(true){
        auto ait = alice.end();
        for(auto it = alice.begin(); it != alice.end(); ++it){
            if(bob.count(*it)){
                ait = it;
                break;
            }
        }
        if(ait == alice.end()) break;
        Card c = *ait;
        cout << "Alice picked matching card " << c.toString() << endl;
        alice.erase(c);
        bob.erase(c);

        auto bit = bob.rend();
        for(auto it = bob.rbegin(); it != bob.rend(); --it){
            if(alice.count(*it)){
                bit = it;
                break;
            }
        }
        if(bit == bob.rend()) break;
        c = *bit;
        cout << "Bob picked matching card " << c.toString() << endl;
        alice.erase(c);
        bob.erase(c);
    }

    cout << "\nAlice's cards:" << endl;
    for(auto& c : alice){
        cout << c.toString() << endl;
    }

    cout << "\nBob's cards:" << endl;
    for(auto& c : bob){
        cout << c.toString() << endl;
    }

    return 0;
}
