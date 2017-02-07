#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "card.h"
#include "deck.h"

using namespace::std;

int main() {
    std::srand(std::time(0));
    cout << endl << "Unshuffled Deck:\n" << endl;
    Deck d = Deck();
    cout << d;
    cout << endl << "Shuffled Deck:\n" << endl;
    d.shuffleDeck();
    cout << d;

    return 0;
}