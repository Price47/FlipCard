#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "card.h"
#include "deck.h"
#include "gameState.h"

using namespace::std;

void printDeckValues(Deck d){
    string buffer = "~~~~~~~~~~~~~~~~~~~~~~~~~";
    cout << buffer << endl;
    d.printDeckValues();
    cout << buffer << endl;
}


// Play Flip function. The cards will be displayed to the screen
// for verification of functionality. The number next to the card
// will correspond to the number in the game output
void playFlip(gameState gs){
    cout << "\nCards in this game: \n";
    printDeckValues(gs.getDeck());
    cout << gs;
    for(int i = 0; i<gs.getDeck().getDeckSize(); i++){
        gs.setupTurn();
        cout << gs;
    }
}

int main() {
    // The replace function never seems necessary, here it is
    // in use though: the top 3 card of the unshuffled deck,
    // then c1 gets the top card which is removed from deck, and the replaced,
    // on bottom
//    Deck d1 = Deck().drawCards(3);
//    printDeckValues(d1);
//    Card *c1 = d1.deal();
//    printDeckValues(d1);
//    d1.replace(c1);
//    Card c2 = *c1;
//    printDeckValues(d1);
//    d1.destroy();
//
//
//
//    // flip card c2 and print, to test the overloaded assignment operator
//    c2.flip();
//    cout << c2;

    // seed random,  create deck, print it, shuffle it 3 times,
    // draw 24 cards, setup the game state, and then play
    std::srand(std::time(0));
    Deck d = Deck();
    d.shuffleDeckNTimes(3);
    Deck d24 = d.drawCards(24);
    cout << "Cards remaining in deck:\n";
    printDeckValues(d);
    gameState gs = gameState(d24);

    playFlip(gs);




    return 0;
}