#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

class Card {
private:
    string suit;
    string symbol;
    int value;

public:
    Card(string s, string y, int v) {
        suit = s;
        symbol = y;
        value = v;
    }

    bool operator==(Card c) {
        return showCard() == c.showCard();
    }

    string showCard() {
        return suit + symbol;
    }

    int getValue() {
        return value;
    }

    string getSymbol() {
        return symbol;
    }

    void setValue(int newValue) {
        value = newValue;
    }
};

class Hand {
private:
    vector<Card> hand;
public:
    void addCard(Card card) {
        hand.push_back(card);
    }

    string getHand() {
        string str = "";
        for (Card i : hand) {
            str += i.showCard() + " ";
        }
        return str;
    }
};

class Deck {
private:
    string suits[4] = {"♠", "♣", "♥", "♦"};
    string symbols[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    int values[13] = {11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
    static vector<Card> deck;

public:
    Deck() {
        while (deck.size() < 52) {
            for (string suit : suits) {
                int i = 0;
                for (string symbol : symbols) {
                    deck.push_back(Card(suit, symbol, values[i]));
                    i++;
                }
            }
        }
    }

    void shuffleDeck() {
        static mt19937 gen(random_device{}());
        shuffle(deck.begin(), deck.end(), gen);
    }

    Card getCard(int i) {
        return deck[51 - i];
    }

    void showDeck() {
        for (Card c : deck) {
            cout << c.showCard() << " ";
        }
        cout << endl;
    }
};

class Game {
private:
    int index = 0;
    int playerTotal = 0;
    int dealerTotal = 0;
    Hand playerHand;
    Hand dealerHand;
    Deck deck;

public:
    Game() {
        deck.shuffleDeck();
        playerDraw();
        dealerDraw();
        playerDraw();
        showHands();
    }
    
    void playerDraw() {
        Card drawnCard = deck.getCard(index++);
        playerHand.addCard(drawnCard);
        playerTotal += drawnCard.getValue();
    }
    
    void dealerDraw() {
        Card drawnCard = deck.getCard(index++);
        dealerHand.addCard(drawnCard);
        dealerTotal += drawnCard.getValue();
    }
    
    void showHands() {
        cout << "Dealer's Hand:\t" << dealerHand.getHand() << "(" << dealerTotal << ")" << endl;
        cout << "Your Hand:\t" << playerHand.getHand() << "(" << playerTotal << ")" << endl;
    }
};

vector<Card> Deck::deck = {};

int main() {
    Game game;
    return 0;
}