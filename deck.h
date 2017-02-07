//
// Created by Price on 2/2/17.
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
    void printDeckOrder();
    Deck drawCards(int n);
    int getDeckSize() const;
    void setDeckSize(int deckSize);
    Card *getRoot() const;
    void setRoot(Card *root);
    Card *getLast() const;
    void setLast(Card *last);
    void addCard(Card *c);
    vector<Card>  linkedListToVector();
    void vectorToLinkedList(vector<Card> vec);
    void printList(vector<Card> vec);
    void shuffleDeck();
private:
    int deckSize = 52;
    Card *root = NULL;
    Card *last = NULL;
    void randomizeVector(vector<Card> &vec);

};

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

void Deck::addCard(Card *c) {
    if(root == NULL) {
        root = c;
        last = c;
    }
    else{
        last->setNext(c);
        c->setPrev(last);
        last = c;
    }
}

Deck Deck::drawCards(int n) {
    Deck d = Deck(n);
    Card *c = new Card();
    *c = *root;
    d.addCard(c);
    for(int i = 0; i < n-1; i++){
        Card *c1 = new Card();
        c = c->getNext();
        *c1 = *c;
        d.addCard(c1);
    }
    d.last->setNext(NULL);
    return d;
}

void Deck::printDeck() {
    if(root) {
        Card *c = root;
        while (c->getNext() != NULL) {
            cout << *c;
            c = c->getNext();
        }
        cout << *last;
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

void Deck::vectorToLinkedList(vector<Card> vec) {
    vector<Card>::iterator vec_it;
    for(vec_it = vec.begin(); vec_it!=vec.end(); vec_it++) {
        Card *c = new Card(vec_it->getValue(), vec_it->getSuit());
        if(vec_it == vec.begin()){
            root = c;
        }
        else {
            addCard(c);
        }
    }
}

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

void Deck::printList(vector<Card> vec) {
    vector<Card>::iterator vec_it;
    for(vec_it = vec.begin(); vec_it!=vec.end(); vec_it++){
        cout << *vec_it;
    }
}

// random shuffle function //
int randomizer (int i) {
    return rand()%i;
}

void Deck::randomizeVector(vector<Card> &vec){
    random_shuffle(vec.begin(), vec.end(), randomizer);
}

// shuffle deck the n times //
void Deck::shuffleDeck() {
    vector<Card> deck = linkedListToVector();
    randomizeVector(deck);
    vectorToLinkedList(deck);
}

ostream& operator<<(ostream& os, Deck d){
    d.printDeck();
    return os;
}
#endif //FLIPCARD_DECK_H

