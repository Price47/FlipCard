//
// Created by Price on 2/2/17.
//

#ifndef FLIPCARD_CARD_H
#define FLIPCARD_CARD_H

using namespace::std;

enum Suit : int {Clubs, Diamonds, Hearts, Spades};

class Card{
    public:
        Card();
        Card(int value, Suit suit);
        int getValue() const;
        void setValue(int value);
        Suit getSuit() const;
        void setSuit(Suit suit);
        string SuitMap();
        string CardMap();
        void setPrev(Card *c);
        void setNext(Card *c);
        Card *getNext() const;
        Card *getPrev() const;

private:
        int value;
        Suit suit;
        Card *next = NULL;
        Card *prev = NULL;

};

Card::Card(){}

Card::Card(int value, Suit suit){
    setValue(value);
    setSuit(suit);
}

int Card::getValue() const {
    return value;
}

void Card::setValue(int value) {
    Card::value = value;
}

Suit Card::getSuit() const {
    return suit;
}

void Card::setSuit(Suit suit) {
    Card::suit = suit;
}

void Card::setPrev(Card *c) {
    Card::prev = c;
}

Card *Card::getNext() const {
    return next;
}

Card *Card::getPrev() const {
    return prev;
}

void Card::setNext(Card *c) {
    Card::next = c;
}

string Card::SuitMap() {
    switch(getSuit()){
        case Clubs: return "Clubs";
        case Diamonds: return "Diamonds";
        case Hearts: return "Hearts";
        case Spades: return "Spades";
        default: return "Invalid Suit";
    }
}

string Card::CardMap(){
    switch(getValue()){
        case 0: return "Ace";
        case 1: return "2";
        case 2: return "3";
        case 3: return "4";
        case 4: return "5";
        case 5: return "6";
        case 6: return "7";
        case 7: return "8";
        case 8: return "9";
        case 9: return "10";
        case 10: return "Jack";
        case 11: return "Queen";
        case 12: return "King";
        default: return "Invalid card value";
    }
}

ostream& operator<<(ostream& os, Card c){
    os << "[ " << c.CardMap() << " of " << c.SuitMap() << " ]" << endl;
    return os;
}
#endif //FLIPCARD_CARD_H
