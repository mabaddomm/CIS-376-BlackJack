//Include guards for our game.h file
#ifndef     __H_GAME__
#define     __H_GAME__

#include <iostream>
#include <vector>
class Deck;
class Card;

enum playerOptions {HIT, STAND, DOUBLEDOWN};


class Game {

    private: 
        //Deck deck;
        int cardIndex = 2;
        std::vector<Card> playerCards;
        std::vector<Card> computerCards;
        int playerMoney = 100;
        int computerMoney = 100;

    public: 
        Game();

        void startGame(Deck& deck);

        void placeBets();

        void playerTurn(Deck& deck);

        void comCards(Deck& deck);

        void computerTurn(Deck& deck);

        void checkRound();

        void endOfGame();  


};

#endif
