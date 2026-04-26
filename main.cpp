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

    Card() { }

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
    Card dealerHiddenCard;
    Deck deck;
    bool winner;
    bool finished = 0;

public:
    Game() {
        deck.shuffleDeck();
        playerDraw();
        dealerDraw();
        playerDraw();
        dealerHiddenCard = deck.getCard(index++);
        showHands();
        if (playerTotal == 21) {
            winner = 1;
            gameOver();
        }
        while (!finished) {
            int input;
            cout << "1. Hit\n2. Stand" << endl;
            cin >> input;
            input == 1 ? hit() : stand();
        }
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

    void hit() {
        system("clear");
        playerDraw();
        showHands();
        if (playerTotal > 21) {
            winner = 0;
            gameOver();
        } else if (playerTotal == 21) {
            winner = 1;
            gameOver();
        }
    }

    void stand() {
        system("clear");
        string dummy;
        dealerHand.addCard(dealerHiddenCard);
        dealerTotal += dealerHiddenCard.getValue();
        cin.ignore();
        while (dealerTotal < 17) {
            system("clear");
            showHands();
            cout << "Enter to Continue:" << endl;
            getline(cin, dummy);
            dealerDraw();
        } 
        system("clear");
        showHands();
        dealerTotal > 21 || dealerTotal < playerTotal ? winner = 1 : winner = 0;
        gameOver();
    }

    void gameOver() {
        finished = 1;
        if (winner == 1) {
            cout << "You Win!" << endl;
        } else if (winner == 0) {
            cout << (playerTotal == dealerTotal ? "You've Drawn." : "You Lose") << endl;
        }
    }
    
    void showHands() {
        cout << "Dealer's Hand:\t" << dealerHand.getHand() << "(" << dealerTotal << ")" << endl;
        cout << "Your Hand:\t" << playerHand.getHand() << "(" << playerTotal << ")\n" << endl;
    }
};

vector<Card> Deck::deck = {};

int main() {
    system("clear");
    Game game;
    return 0;
}