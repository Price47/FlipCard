//
// Deck object. contains a linked list of card objects.
//

#ifndef FLIPCARD_DECK_H
#define FLIPCARD_DECK_H

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <random>
#include "card.h"

using namespace::std;

class Deck{
public:
    Deck();
    Deck(int n);
    void printDeck();
    void printDeckValues();
    Deck drawCards(int n);
    int getDeckSize() const;
    void setDeckSize(int deckSize);
    Card *getRoot() const;
    void setRoot(Card *root);
    Card *getLast() const;
    void setLast(Card *last);
    void shuffleDeckNTimes(int n);
    Card *findCard(int n);
    Card *deal();
    void replace(Card *c);
    void removeCard(Card *c);
    void destroy();
private:
    int deckSize = 52;
    Card *root = NULL;
    Card *last = NULL;
    void randomizeVector(vector<Card> &vec);
    void shuffleDeck();
    void addCard(Card *c);
    vector<Card>  linkedListToVector();
    void vectorToLinkedList(vector<Card> vec);
};

// primary constructor. Creates 13 cards for 4 suits
// (ace - king, club - spade)
Deck::Deck() {
    for(int i = Clubs; i < Spades+1; i++){
        for(int j = 0; j < 13; j++){
            Card *c = new Card(j, Suit(i));
            addCard(c);
        }
    }
}

Deck::Deck(int n) {
    setDeckSize(n);
}

// add a card to the deck //
void Deck::addCard(Card *c) {
    if(getRoot() == NULL) {
        setRoot(c);
        setLast(c);
    }
    else{
        last->setNext(c);
        c->setPrev(last);
        setLast(c);
    }
}

// return top card of the deck and remove that card from
// the deck
Card *Deck::deal(){
    if(root) {
        Card *c = new Card(root->getValue(), root->getSuit());
        Card *old_root = root;
        if (root->getNext() != NULL) {
            root = root->getNext();
        }
        delete (old_root);
        return c;
    }
    return NULL;
}

void Deck::replace(Card *c) {
    c->setPrev(last);
    c->setNext(NULL);
    last->setNext(c);
    last = last->getNext();
}

// function to be used in part b, draw n cards from a deck and return as a
// new deck //
Deck Deck::drawCards(int n) {
    Deck d = Deck(n);
    for(int i = 0; i < n; i++){
        //Card *c1 = new Card();
        Card *c1 = deal();
        c1->setId(i);
        d.addCard(c1);
    }
    d.last->setNext(NULL);
    return d;
}

// locate a specific card in the deck. In this case, the card
// being located is the the face down card chosen by the user.
// returns that card.
Card *Deck::findCard(int id){
    Card *c = root;
    while(c->getNext()!=NULL) {
        if (c->getId() == id) {
            return c;
        }
        else{
            c=c->getNext();
        }
    }
    if(c->getNext() == NULL && c->getId() == id){
        return c;
    }
    return NULL;
}

// remove card c and bridge the gab between in the linked list
void Deck::removeCard(Card *c) {
    if(c->getNext()!= NULL & c->getPrev()!=NULL){
        Card *prev = c->getPrev();
        Card *next = c->getNext();

        next->setPrev(prev);
        prev->setNext(next);
        delete(c);
    }
}

void Deck::printDeck() {
    if(getRoot()) {
        Card *c = getRoot();
        while (c->getNext() != NULL) {
            cout << *c;
            c = c->getNext();
        }
        cout << *getLast();
    }
}

// Display the values of card, even if they are "flipped over."
// Only used in the main function to output the cards in the
// 24 card hand, and the remaining cards in the deck,
// as per assignment instructions
void Deck::printDeckValues() {
    if(getRoot()) {
        Card *c = getRoot();
        while (c->getNext() != NULL) {
            c->flip();
            cout << "( " << c->getId() << " )" << *c << endl;
            c->flip();
            c = c->getNext();
        }
        Card *last = getLast();
        last->flip();
        cout << "( " << c->getId() << " )" << *last << endl;
        last->flip();
    }
}

int Deck::getDeckSize() const {
    return deckSize;
}

void Deck::setDeckSize(int deckSize) {
    Deck::deckSize = deckSize;
}

Card *Deck::getRoot() const {
    return root;
}

void Deck::setRoot(Card *root) {
    Deck::root = root;
}

Card *Deck::getLast() const {
    return last;
}

void Deck::setLast(Card *last) {
    Deck::last = last;
}

// apply vector of cards to the linked list which makes the deck //
void Deck::vectorToLinkedList(vector<Card> vec) {
    vector<Card>::iterator vec_it;
    for(vec_it = vec.begin(); vec_it!=vec.end(); vec_it++) {
        Card *c = new Card(vec_it->getValue(), vec_it->getSuit());
        if(vec_it == vec.begin()){
            setRoot(c);
        }
        else {
            addCard(c);
        }
    }
}

// apply the linked list of cards in the deck to a vector, which
// can more easily be randomly reordered. //
vector<Card> Deck::linkedListToVector() {
    vector<Card> cards;
    Card *c = root;
    cards.push_back(*root);
    while(c->getNext() != NULL){
        c = c->getNext();
        cards.push_back(*c);
        delete(c);
    }
    return cards;
}

// random shuffle function //
int randomizer (int i) {
    return rand()%i;
}

// randomize the deck //
void Deck::randomizeVector(vector<Card> &vec){
    random_shuffle(vec.begin(), vec.end(), randomizer);
}

// public shuffle deck function. apply linked list to a vector of cards, //
// randomize the vector, and then apply the vector back to a linked list //
void Deck::shuffleDeck() {
    vector<Card> deck = linkedListToVector();
    randomizeVector(deck);
    vectorToLinkedList(deck);
}

void Deck::shuffleDeckNTimes(int n){
    for(int i=0;i<n;i++){
        shuffleDeck();
    }
}

// iterate through deck, and delete all pointers
void Deck::destroy() {
    if(root){
        Card *c = root;
        while(c->getNext()!=NULL){
            c = c->getNext();
            delete(c->getPrev());
        }
        delete(last);
    }
}
// overloaded operator to print deck //
ostream& operator<<(ostream& os, Deck d){
    d.printDeck();
    return os;
}
#endif //FLIPCARD_DECK_H

