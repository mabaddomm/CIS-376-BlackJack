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
        int cardIndex = 2;
        std::vector<Card> playerCards;
        std::vector<Card> computerCards;

    public: 
        Game();

        void startGame(Deck& deck);

        void startOfRound();

        void playerTurn(Deck& deck);

        void computerTurn(Deck& deck);

        void checkRound();

        void endOfGame();  


};

#endif
