#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include "card.h"
using namespace std;
int main(int argc,char** argv){
    if(argc<3){ cout<<"Please provide 2 file names\n"; return 1; }
    ifstream f1(argv[1]),f2(argv[2]);
    if(f1.fail()||f2.fail()){ cout<<"Could not open file "<<(f1.fail()?argv[1]:argv[2])<<"\n"; return 1; }
    set<Card> alice,bob;
    string line;
    while(getline(f1,line)&&!line.empty()){
        istringstream iss(line); char sc; string vs; iss>>sc>>vs;
        alice.insert(Card::fromChars(sc,vs));
    }
    while(getline(f2,line)&&!line.empty()){
        istringstream iss(line); char sc; string vs; iss>>sc>>vs;
        bob.insert(Card::fromChars(sc,vs));
    }
    for(;;){
        auto ait=alice.end();
        for(auto it=alice.begin();it!=alice.end();++it)
            if(bob.count(*it)){ ait=it; break; }
        if(ait==alice.end()) break;
        Card c=*ait;
        cout<<"Alice picked matching card "<<c.toString()<<"\n";
        alice.erase(c); bob.erase(c);
        auto bit=bob.rend();
        for(auto it=bob.rbegin();it!=bob.rend();--it)
            if(alice.count(*it)){ bit=it; break; }
        if(bit==bob.rend()) break;
        c=*bit;
        cout<<"Bob picked matching card "<<c.toString()<<"\n";
        alice.erase(c); bob.erase(c);
    }
    cout<<"\nAlice's cards:\n";
    for(auto&c:alice) cout<<c.toString()<<"\n";
    cout<<"\nBob's cards:\n";
    for(auto&c:bob)   cout<<c.toString()<<"\n";
    return 0;
}
