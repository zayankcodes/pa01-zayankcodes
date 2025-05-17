#include "card.h"
#include "card_list.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cassert>

void testInsertContains() {
    bst t;
    Card a = Card::fromChars('c', "a");
    assert(!t.contains(a));
    t.insert(a);
    assert(t.contains(a));
    t.insert(a);
    assert(t.contains(a));
    Card b = Card::fromChars('d', "5"), c = Card::fromChars('h', "k");
    t.insert(b);
    t.insert(c);
    assert(t.contains(b) && t.contains(c));
    assert(!t.contains(Card::fromChars('s', "2")));
}

void testRemove() {
    bst t;
    Card a = Card::fromChars('c', "3");
    Card b = Card::fromChars('d', "a");
    t.insert(a);
    t.insert(b);
    t.remove(a);
    assert(!t.contains(a) && t.contains(b));
    t.remove(a);
    assert(!t.contains(a));
    t.remove(b);
    assert(!t.contains(b));
    bst e;
    e.remove(a);
    assert(!e.contains(a));
}

void testPrintDeck() {
    {
        bst t;
        std::ostringstream oss;
        auto old = std::cout.rdbuf(oss.rdbuf());
        t.printDeck();
        assert(oss.str().empty());
        oss.str("");
        oss.clear();
        t.insert(Card::fromChars('s', "2"));
        t.printDeck();
        assert(oss.str() == "s 2\n");
        std::cout.rdbuf(old);
    }
    {
        bst t;
        t.insert(Card::fromChars('s', "2"));
        t.insert(Card::fromChars('c', "k"));
        t.insert(Card::fromChars('h', "5"));
        std::ostringstream oss;
        auto old = std::cout.rdbuf(oss.rdbuf());
        t.printDeck();
        assert(oss.str() == "c k\ns 2\nh 5\n");
        std::cout.rdbuf(old);
    }
    {
        bst t;
        t.insert(Card::fromChars('c', "4"));
        t.insert(Card::fromChars('h', "2"));
        t.insert(Card::fromChars('s', "3"));
        std::ostringstream oss;
        auto old = std::cout.rdbuf(oss.rdbuf());
        t.printDeck();
        assert(oss.str() == "c 4\ns 3\nh 2\n");
        std::cout.rdbuf(old);
    }
    {
        bst t;
        t.insert(Card::fromChars('d', "7"));
        t.insert(Card::fromChars('d', "7"));
        std::ostringstream oss;
        auto old = std::cout.rdbuf(oss.rdbuf());
        t.printDeck();
        assert(oss.str() == "d 7\n");
        std::cout.rdbuf(old);
    }
    {
        bst t;
        t.insert(Card::fromChars('c', "9"));
        t.remove(Card::fromChars('c', "9"));
        std::ostringstream oss;
        auto old = std::cout.rdbuf(oss.rdbuf());
        t.printDeck();
        assert(oss.str().empty());
        std::cout.rdbuf(old);
    }
}

void testSuccessorPredecessor() {
    bst t;
    Card c1 = Card::fromChars('c', "a");
    bool thrown = false;
    try { t.getSuccessorNode(c1); } catch (...) { thrown = true; }
    assert(thrown);
    t.insert(c1);
    thrown = false;
    try { t.getSuccessorNode(c1); } catch (...) { thrown = true; }
    assert(thrown);
    thrown = false;
    try { t.getPredecessorNode(c1); } catch (...) { thrown = true; }
    assert(thrown);
    Card c2 = Card::fromChars('c', "3"), c3 = Card::fromChars('d', "2");
    t.insert(c2);
    t.insert(c3);
    assert(t.getSuccessorNode(c1) == c2);
    assert(t.getSuccessorNode(c2) == c3);
    assert(t.getPredecessorNode(c3) == c2);
    assert(t.getPredecessorNode(c2) == c1);
    thrown = false;
    try { t.getSuccessorNode(c3); } catch (...) { thrown = true; }
    assert(thrown);
}

void testIteratorEmpty() {
    bst t;
    assert(t.begin() == t.end());
    assert(t.rbegin() == t.rend());
}

void testIteratorSingle() {
    bst t;
    Card c = Card::fromChars('h', "7");
    t.insert(c);
    auto it = t.begin();
    assert(it != t.end());
    assert(*it == c);
    ++it;
    assert(it == t.end());
    it = t.rbegin();
    assert(*it == c);
    --it;
    assert(it == t.rend());
}

void testIteratorMultiple() {
    bst t;
    std::vector<Card> v = {
        Card::fromChars('c', "2"),
        Card::fromChars('d', "5"),
        Card::fromChars('h', "a")
    };
    for (auto& c : v) t.insert(c);
    std::vector<Card> out;
    for (auto it = t.begin(); it != t.end(); ++it) out.push_back(*it);
    std::sort(v.begin(), v.end());
    assert(out == v);
    out.clear();
    for (auto it = t.rbegin(); it != t.rend(); --it) out.push_back(*it);
    std::reverse(v.begin(), v.end());
    assert(out == v);
}

void testIteratorSafePastEnds() {
    bst t;
    t.insert(Card::fromChars('s', "3"));
    t.insert(Card::fromChars('h', "2"));
    auto it = t.end();
    --it;
    ++it;
    assert(it == t.end());
}

void testPlayGameCommon() {
    bst a, b;
    a.insert(Card::fromChars('c', "a"));
    a.insert(Card::fromChars('d', "5"));
    b.insert(Card::fromChars('d', "5"));
    b.insert(Card::fromChars('h', "k"));
    std::ostringstream oss;
    auto old = std::cout.rdbuf(oss.rdbuf());
    playGame(a, b);
    std::cout.rdbuf(old);
    std::string out = oss.str();
    assert(out.find("Alice picked matching card d 5\n") != std::string::npos);
    assert(out.find("\nAlice's cards:\n") != std::string::npos);
    assert(out.find("c a\n") != std::string::npos);
    assert(out.find("\nBob's cards:\n") != std::string::npos);
    assert(out.find("h k\n") != std::string::npos);
}

void testPlayGameEmptyAlice() {
    bst a, b;
    b.insert(Card::fromChars('c', "2"));
    std::ostringstream oss;
    auto old = std::cout.rdbuf(oss.rdbuf());
    playGame(a, b);
    std::cout.rdbuf(old);
    std::string out = oss.str();
    assert(out.find("c 2\n") != std::string::npos);
}

void testPlayGameNoCommon() {
    bst a, b;
    a.insert(Card::fromChars('c', "3"));
    b.insert(Card::fromChars('d', "4"));
    std::ostringstream oss;
    auto old = std::cout.rdbuf(oss.rdbuf());
    playGame(a, b);
    std::cout.rdbuf(old);
    std::string out = oss.str();
    assert(out.find("c 3\n") != std::string::npos);
    assert(out.find("d 4\n") != std::string::npos);
}

int main() {
    testInsertContains();
    testRemove();
    testPrintDeck();
    testSuccessorPredecessor();
    testIteratorEmpty();
    testIteratorSingle();
    testIteratorMultiple();
    testIteratorSafePastEnds();
    testPlayGameCommon();
    testPlayGameEmptyAlice();
    testPlayGameNoCommon();
    std::cout << "All tests passed!\n";
    return 0;
}
