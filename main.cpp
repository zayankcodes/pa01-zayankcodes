#include <iostream>
#include <fstream>
#include <sstream>
#include "card.h"
#include "card_list.h"

int main(int argc,char** argv){
    if(argc<3){ std::cout<<"Please provide 2 file names\n"; return 1; }
    std::ifstream f1(argv[1]),f2(argv[2]);
    if(f1.fail()||f2.fail()){ std::cout<<"Could not open file "<<(f1.fail()?argv[1]:argv[2])<<"\n"; return 1; }
    bst alice,bob;
    std::string line;
    while(std::getline(f1,line)&&!line.empty()){
        std::istringstream iss(line); char sc; std::string vs; iss>>sc>>vs;
        alice.insert(Card::fromChars(sc,vs));
    }
    while(std::getline(f2,line)&&!line.empty()){
        std::istringstream iss(line); char sc; std::string vs; iss>>sc>>vs;
        bob.insert(Card::fromChars(sc,vs));
    }
    playGame(alice,bob);
    return 0;
}
