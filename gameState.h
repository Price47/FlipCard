//
// Class to handle the game state and points,
// and an overloaded operator to print the game state.
// Also handles the display of the game, 24 card face down on the
// table that the user can choose to flip
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
    void endGame();
    bool verifyResponse(string s);
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
// print 6 card to a row
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

// print 4 rows of card
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

// assign point values to cards: 2-6, lose all points;
// 7, lose half points; 8-10 no change in points;
// jack-king add 5 points; ace add 10 points (note
// ace is 0). After performing point changes, add 1 point
// for a heart
void gameState::pointMap(Card c){
    switch(c.getValue()){
        case 0: setPoints(getPoints() + 10); break;
        case 1: setPoints(0); break;
        case 2: setPoints(0); break;
        case 3: setPoints(0); break;
        case 4: setPoints(0); break;
        case 5: setPoints(0); break;
        case 6: setPoints(((getPoints())/2)); break;
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

// Read which card to flip, then flip it and change gamestate points
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
        if(!c->getFlipped()) {
            pointMap(*c);
            c->flip();
        }
        else{
            cout << "That card has already been flipped\n";
        }
    }

}

// end game, print score, and exit with code 0
void gameState::endGame() {
    cout << "Congratualtions, your final score is " << getPoints() << " point(s)\n";
    deck.destroy();
    exit(0);
}

bool gameState::verifyResponse(string s){
    bool verified = (s == "y" | s == "Y" | s == "N" | s == "n");
    if(!verified){
        cout << "Response must be Y, y, N, or n\n";
        return false;
    }
    return true;
}

// see if user wants to end the game, or continue flipping
void gameState::setupTurn(){
    string drawCard, finish;
    bool finishedSetup = false;
    while(!finishedSetup) {
        cout << "You can flip a card, or stop now. would you like to pick another card? (Y/N)\n";
        cin >> drawCard;
        if(verifyResponse(drawCard)) {
            if (!resolveChoice(drawCard)) {
                cout << "Are you sure you want to exit? (Y/N)\n";
                cin >> finish;
                if (resolveChoice(finish)) {
                    endGame();
                } else {
                    continue;
                }
            } else {
                finishedSetup = true;
            }
        }
        else{
            finishedSetup = false;
        }
    }
    playTurn();
}

ostream& operator<<(ostream& os, gameState gs){
    gs.printGame();
    cout << "POINTS: " << gs.getPoints() << endl;
    return os;
}
#endif //FLIPCARD_GAMESTATE_H
