#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "card.h"
#include "deck.h"
#include "gameState.h"

using namespace::std;

string buffer = "~~~~~~~~~~~~~~~~~~~~~~~~~";

void playFlip(gameState gs){
    cout << "Cards in this hand: \n" << buffer << endl;
    gs.getDeck().printDeckValues();
    cout << buffer << endl;
    cout << gs;
    for(int i = 0; i<gs.getDeck().getDeckSize(); i++){
        gs.setupTurn();
        cout << gs;
    }
}

int main() {
    // seed random,  create deck, print it, shuffle it,
    // draw 24 cards, setup the game state, and then play
    std::srand(std::time(0));
    Deck d = Deck();
    d.shuffleDeckNTimes(3);
    Deck d24 = d.drawCards(24);
    gameState gs = gameState(d24);

    playFlip(gs);

//    Deck d = Deck();
//    Deck d2 = d.drawCards(3);
//    cout << d2;
//    Card *c = d2.deal();
//    cout << d2;
//    cout << *c;

//    Deck d = Deck();
//    Deck d2 = d.drawCards(3);
//    d2.printDeckValues();
//    Card *c = new Card(11,Spades,5);
//    d2.replace(c);
//    d2.printDeckValues();



    return 0;
}