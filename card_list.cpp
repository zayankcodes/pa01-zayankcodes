#include "card_list.h"

void bst::clear(Node* n){
    if(!n) return;
    clear(n->left);
    clear(n->right);
    delete n;
}

bst::Node* bst::findNode(const Card& k) const{
    Node* cur=root;
    while(cur){
        if(k==cur->data) return cur;
        else if(k<cur->data) cur=cur->left;
        else cur=cur->right;
    }
    return nullptr;
}

bst::Node* bst::minimum(Node* n) const{
    while(n&&n->left) n=n->left;
    return n;
}

bst::Node* bst::maximum(Node* n) const{
    while(n&&n->right) n=n->right;
    return n;
}

void bst::transplant(Node* u,Node* v){
    if(!u->parent) root=v;
    else if(u==u->parent->left) u->parent->left=v;
    else u->parent->right=v;
    if(v) v->parent=u->parent;
}

void bst::removeNode(Node* z){
    if(!z->left) transplant(z,z->right);
    else if(!z->right) transplant(z,z->left);
    else{
        Node* y=minimum(z->right);
        if(y->parent!=z){
            transplant(y,y->right);
            y->right=z->right;
            y->right->parent=y;
        }
        transplant(z,y);
        y->left=z->left;
        y->left->parent=y;
    }
    delete z;
}

bst::Node* bst::successorNode(Node* x) const{
    if(!x) return nullptr;
    if(x->right) return minimum(x->right);
    Node* y=x->parent;
    while(y&&x==y->right){ x=y; y=y->parent; }
    return y;
}

bst::Node* bst::predecessorNode(Node* x) const{
    if(!x) return nullptr;
    if(x->left) return maximum(x->left);
    Node* y=x->parent;
    while(y&&x==y->left){ x=y; y=y->parent; }
    return y;
}

bst::bst():root(nullptr){}
bst::~bst(){ clear(root); }

void bst::insert(const Card& k){
    Node *y=nullptr,*x=root;
    while(x){
        y=x;
        if(k<x->data) x=x->left;
        else if(x->data<k) x=x->right;
        else return;
    }
    Node* z=new Node(k);
    z->parent=y;
    if(!y) root=z;
    else if(k<y->data) y->left=z;
    else y->right=z;
}

bool bst::contains(const Card& k)const{
    return findNode(k)!=nullptr;
}

void bst::remove(const Card& k){
    Node* z=findNode(k);
    if(z) removeNode(z);
}

void bst::printDeck()const{
    std::function<void(Node*)> in=[&](Node* n){
        if(!n) return;
        in(n->left);
        std::cout<<n->data.toString()<<"\n";
        in(n->right);
    };
    in(root);
}

Card bst::getSuccessorNode(const Card& k)const{
    Node* z=findNode(k);
    if(!z) throw std::invalid_argument("Card not found");
    Node* s=successorNode(z);
    if(!s) throw std::out_of_range("No successor");
    return s->data;
}

Card bst::getPredecessorNode(const Card& k)const{
    Node* z=findNode(k);
    if(!z) throw std::invalid_argument("Card not found");
    Node* p=predecessorNode(z);
    if(!p) throw std::out_of_range("No predecessor");
    return p->data;
}

bst::Iterator bst::begin() const{ return Iterator(minimum(root),this); }
bst::Iterator bst::end()   const{ return Iterator(nullptr,this); }
bst::Iterator bst::rbegin()const{ return Iterator(maximum(root),this); }
bst::Iterator bst::rend()  const{ return Iterator(nullptr,this); }

void playGame(bst& alice,bst& bob){
    while(true){
        auto ait=alice.end();
        for(auto it=alice.begin();it!=alice.end();++it)
            if(bob.contains(*it)){ ait=it; break; }
        if(ait==alice.end()) break;
        Card c=*ait;
        std::cout<<"Alice picked matching card "<<c.toString()<<"\n";
        alice.remove(c); bob.remove(c);

        auto bit=bob.rend();
        for(auto it=bob.rbegin();it!=bob.rend();--it)
            if(alice.contains(*it)){ bit=it; break; }
        if(bit==bob.rend()) break;
        c=*bit;
        std::cout<<"Bob picked matching card "<<c.toString()<<"\n";
        alice.remove(c); bob.remove(c);
    }
    std::cout<<"\nAlice's cards:\n";
    alice.printDeck();
    std::cout<<"\nBob's cards:\n";
    bob.printDeck();
}
