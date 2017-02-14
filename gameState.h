//
// Created by Price on 2/11/17.
//

#ifndef FLIPCARD_GAMESTATE_H
#define FLIPCARD_GAMESTATE_H

#include "deck.h"
#include "card.h"

using namespace::std;

class gameState{
public:
    gameState();
    gameState(Deck d);
    Deck getDeck();
    void setDeck(Deck d);
    void printRow();
    void printGame();
    Card *getDeckPosition() const;
    void setDeckPosition(Card *deckPosition);
    void setupTurn();
    void playTurn();
    double getPoints();
    void setPoints(double points);
private:
    Deck deck;
    Card *deckPosition;
    int points = 0;
    bool resolveChoice(string s);
    bool resolveCardChoice(int n);
    void pointMap(Card c);
};

gameState::gameState() {}

gameState::gameState(Deck d){
    setDeck(d);
    setDeckPosition(d.getRoot());
}

void gameState::setDeck(Deck d) {
    gameState::deck = d;
}

Deck gameState::getDeck(){
    return gameState::deck;
}

void gameState::printRow(){
    Deck d = getDeck();
    Card *c = deckPosition;
    int i=0;
    while (c->getNext() != NULL && i<6) {
        cout << *c;
        c = c->getNext();
        setDeckPosition(c);
        i++;
    }
    if(c->getNext() == NULL){
        cout << *c;
    }
}

void gameState::printGame() {
    for(int i =0; i<4; i++){
        printRow();
        cout << endl;
    }
}

Card *gameState::getDeckPosition() const {
    return deckPosition;
}

void gameState::setDeckPosition(Card *deckPosition) {
    gameState::deckPosition = deckPosition;
}

bool gameState::resolveChoice(string s){
    return s == "Y" | s == "y";
}

double gameState::getPoints() {
    return gameState::points;
}

void gameState::setPoints(double points) {
    gameState::points=points;
}

void gameState::pointMap(Card c){
    switch(c.getValue()){
        case 0: setPoints(getPoints() + 10); break;
        case 1: setPoints(0); break;
        case 2: setPoints(0); break;
        case 3: setPoints(0); break;
        case 4: setPoints(0); break;
        case 5: setPoints(0); break;
        case 6: setPoints(47); break;
        case 7: setPoints(getPoints()); break;
        case 8: setPoints(getPoints()); break;
        case 9: setPoints(getPoints()); break;
        case 10: setPoints(getPoints() + 5); break;
        case 11: setPoints(getPoints() + 5); break;
        case 12: setPoints(getPoints() + 5); break;
        default: setPoints(getPoints()); break;
    }

    if(c.getSuit()==Hearts){
        setPoints(getPoints()+1);
    }
}

bool gameState::resolveCardChoice(int n){
    return(n<=deck.getDeckSize());
}
void gameState::playTurn(){
    int cardChoice;
    cout << "Which card would you like to flip?\n";
    cin >> cardChoice;
    while(!resolveCardChoice(cardChoice)){
        cout << "That's an invalid choice. Please enter a valid card number.\n";
        cin >> cardChoice;
    }
    Card *c = deck.findCard(cardChoice);
    if(c){
        pointMap(*c);
        c->flip();
    }

}

void gameState::setupTurn(){
    string drawCard;
    cout << "You can flip a card, or stop now. would you like to pick another card? (Y/N)\n";
    cin >> drawCard;
    if(!resolveChoice(drawCard)){
        exit(0);
    }
    playTurn();
}

ostream& operator<<(ostream& os, gameState gs){
    gs.printGame();
    cout << "POINTS: " << gs.getPoints() << endl;
    return os;
}
#endif //FLIPCARD_GAMESTATE_H
