#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

int myRand() {
    static std::mt19937 gen(std::random_device{}());
    static std::uniform_int_distribution<> dist(0, 51);
    return dist(gen);
}

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
};

class Deck {
private:
    string suits[4] = {"♠", "♣", "♥", "♦"};
    string symbols[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    int values[13] = {11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
    static vector<Card> deck;
public:
#include <random>

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

    Card getCard() {
        srand(time(0));
        return deck[rand() % 52];
    }

    void showDeck() {
        for (Card c : deck) {
            cout << c.showCard() << " ";
        }
        cout << endl;
    }
};

vector<Card> Deck::deck = {};

int main() {
    Deck main = Deck();
    cout << main.getCard().showCard() << endl;
    main.shuffleDeck();
    main.showDeck();
    return 0;
}