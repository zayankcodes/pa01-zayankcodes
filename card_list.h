#ifndef CARD_LIST_H
#define CARD_LIST_H

#include "card.h"
#include <iostream>
#include <functional>
#include <stdexcept>

class bst {
public:
    class Iterator;
    bst();
    ~bst();
    void insert(const Card& key);
    bool contains(const Card& key) const;
    void remove(const Card& key);
    void printDeck() const;
    Card getSuccessorNode(const Card& key) const;
    Card getPredecessorNode(const Card& key) const;
    Iterator begin()  const;
    Iterator end()    const;
    Iterator rbegin() const;
    Iterator rend()   const;
private:
    struct Node {
        Card data;
        Node *left, *right, *parent;
        Node(const Card& c): data(c), left(nullptr), right(nullptr), parent(nullptr) {}
    };
    Node* root;
    void clear(Node* n);
    Node* findNode(const Card& k) const;
    Node* minimum(Node* n) const;
    Node* maximum(Node* n) const;
    void transplant(Node* u, Node* v);
    void removeNode(Node* z);
    Node* successorNode(Node* x)   const;
    Node* predecessorNode(Node* x) const;
};

class bst::Iterator {
    Node* node;
    const bst* tree;
    Node* succ(Node* x) const {
        if (!x) return nullptr;
        if (x->right) return tree->minimum(x->right);
        Node* y = x->parent;
        while (y && x == y->right) { x = y; y = y->parent; }
        return y;
    }
    Node* pred(Node* x) const {
        if (!x) return nullptr;
        if (x->left) return tree->maximum(x->left);
        Node* y = x->parent;
        while (y && x == y->left) { x = y; y = y->parent; }
        return y;
    }
public:
    Iterator(Node* n=nullptr, const bst* t=nullptr): node(n), tree(t) {}
    const Card& operator*()  const { return node->data; }
    const Card* operator->() const { return &node->data; }
    Iterator& operator++()   { node = succ(node); return *this; }
    Iterator  operator++(int){ Iterator tmp=*this; node=succ(node); return tmp; }
    Iterator& operator--() {
        if (!node) node = tree->maximum(tree->root);
        else       node = pred(node);
        return *this;
    }
    Iterator  operator--(int){
        Iterator tmp=*this;
        if (!node) node = tree->maximum(tree->root);
        else       node = pred(node);
        return tmp;
    }
    bool operator==(const Iterator& o) const { return node==o.node; }
    bool operator!=(const Iterator& o) const { return node!=o.node; }
};

void playGame(bst& alice, bst& bob);

#endif
