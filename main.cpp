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
    Card() {
        suit = "Joker";
        symbol = "Joker";
        value = 0;
    }

    Card(string s, string y, int v) {
        suit = s;
        symbol = y;
        value = v;
    }

    string showCard() const { return suit + symbol; }
    int getValue() const { return value; }
    string getSymbol() const { return symbol; }
    void setValue(int newValue) { value = newValue; }
};

class Deck {
    private:
    string suits[4] = {"♠", "♣", "♥", "♦"};
    string symbols[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    int values[13] = {11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
    vector<Card> deck;
    
    public:
    Deck() {
        for (string suit : suits) {
            int i = 0;
            for (string symbol : symbols) {
                deck.push_back(Card(suit, symbol, values[i++]));
            }
        }
        static mt19937 gen(random_device{}());
        shuffle(deck.begin(), deck.end(), gen);
    }
    
    Card getCard() {
        Card card = deck.back();
        deck.pop_back();
        return card;
    }
};

class Hand {
protected:
    vector<Card> hand;
    Deck* deck = nullptr;
    int total = 0;
    bool inPlay = 1;
    
public:
    Hand(Deck* d) {
        deck = d;
        drawCard();
    }

    void finishPlay() {
        inPlay = 0;
    }

    string getHand() const {
        string str = "";
        for (Card i : hand) {
            str += i.showCard() + " ";
        }
        if (getAceCondition() && inPlay) str += getAceString();
        else str += "(" + to_string(getValue()) + ")";
        return str;
    }

    bool getAceCondition() const { return checkAce(); }

    string getAceString() const { return "(" + to_string(getValue()) + "," + to_string(getValue() - 10) + ")"; }

    void drawCard() {
        Card drawnCard = deck->getCard();
        hand.push_back(drawnCard);
        total += drawnCard.getValue();
    }

    bool checkAce() const {
        for (const Card& c : hand) {
            if (c.getSymbol() == "A" && c.getValue() == 11) return 1;
        }
        return 0;
    }

    bool confirmBust() {
        bool aceFound = 0;
        for (Card& c : hand) {
            if (c.getSymbol() == "A" && c.getValue() == 11) {
                c.setValue(1);
                total -= 10;
                aceFound = 1;
            }
        }
        return aceFound;
    }

    int getValue() const { return total; }

    bool operator==(const Hand& h) const { return getValue() == h.getValue(); }
    bool operator==(const int i) const { return getValue() == i; }
    bool operator>(const Hand& h) const { return getValue() > h.getValue(); }
    bool operator>(const int i) const { return getValue() > i; }
    bool operator<(const Hand& h) const { return getValue() < h.getValue(); }
    bool operator<(const int i) const { return getValue() < i; }
    bool operator<=(const Hand& h) const { return getValue() <= h.getValue(); }
    bool operator<=(const int i) const { return getValue() <= i; }
};

class DealerHand : public Hand {
private:
    Card dealerHiddenCard;
    int hiddenCardValue;

public:
    DealerHand(Deck* d) : Hand(d) { };

    void drawHiddenCard() {
        dealerHiddenCard = deck->getCard();
        hiddenCardValue = dealerHiddenCard.getValue();
    }

    void revealHiddenCard() {
        hand.push_back(dealerHiddenCard);
        total += hiddenCardValue;
    }

    bool getAceCondition() const { return checkAce() && getValue() < 17; }
};

class Game {
private:
    Deck deck;
    Hand playerHand = Hand(&deck);
    DealerHand dealerHand = DealerHand(&deck);
    bool winner;
    bool finished = 0;

public:
    Game() {
        playerHand.drawCard();
        dealerHand.drawHiddenCard();
        if (playerHand == 21) {
            dealerHand.revealHiddenCard();
            showHands();
            playerHand == dealerHand ? winner = 0 : winner = 1;
            gameOver();
        }
        if (!finished) { showHands(); }
        while (!finished) {
            int input;
            cout << "1. Hit\n2. Stand" << endl;
            cin >> input;
            input == 1 ? hit() : stand();
        }
    }

    void hit() {
        playerHand.drawCard();
        showHands();
        if (playerHand > 21 && !playerHand.confirmBust()) {
            winner = 0;
            gameOver();
        } 
        if (!finished) { showHands(); }
        if (playerHand == 21) {
            playerHand.finishPlay();
            stand();
        }
    }

    void stand() {
        string dummy;
        cin.ignore();
        dealerHand.revealHiddenCard();
        while (dealerHand < 17 && dealerHand <= playerHand) {
            showHands();
            cout << "Enter to Continue:" << endl;
            getline(cin, dummy);
            dealerHand.drawCard();
            if (dealerHand > 21) dealerHand.confirmBust();
        }
        dealerHand > 21 || dealerHand < playerHand ? winner = 1 : winner = 0;
        gameOver();
    }

    void gameOver() {
        finished = 1;
        playerHand.finishPlay();
        dealerHand.finishPlay();
        
        showHands();
        if (winner == 1) {
            cout << "You Win!" << endl;
        } else if (winner == 0) {
            cout << (playerHand == dealerHand ? "You've Drawn." : "You Lose.") << endl;
        }
    }
    
    void showHands() {
        system("clear");
        cout << "Dealer's Hand:\t" << dealerHand.getHand() << endl;
        cout << "Your Hand:\t" << playerHand.getHand() << endl;
    }
};

int main() {
    system("clear");
    Game game;
    return 0;
}