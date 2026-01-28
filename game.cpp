#include <iostream>
#include "game.h"
#include "deck.h"
#include <random>

Game::Game() { 
    int cardIndex = 2;
    int playerMoney = 100;
    int computerMoney = 100;
    int finalbet;
    int computerBet;
}

void Game::startGame(Deck& deck){
    std::cout << "Welcome To Jack Black" << std::endl;
}

/*This Function Checks to see what bet you place before the game Fully Starts. 
It also takes care of the dealers bet through random number generation I used the random generation we talked about in class 
today*/

void Game::placeBets(){
    //This is all my logic for place a bet for the human player and checking to make sure they have enough money to make the bet
    int betMoney = 0;
    std::cout << "Your Current Amount of Money is " << playerMoney << "!!!\nPlease Enter how Much You Would Like To Bet:";
    std::cin >> betMoney;
    if(betMoney > playerMoney){
        std::cout << "This Bet is more than you have Please Enter an amount Less than" << playerMoney << std::endl;
        placeBets();
    } else {
        int finalBet = betMoney;
    }

    //This random generator thing I used from the random generator that we talked about in class when showing us SDL3
    std::cout << "The Dealer has the following amount of Money: " << computerMoney << std::endl;
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distrib(1, computerMoney);

    int computerBet = distrib(gen);
    std::cout << "The Dealer Places a bet of: $" << computerBet << std::endl;
}

void Game::playerTurn(Deck& deck){
    std::cout << "Here are your two Cards: \n";
    Card playerCardOne = deck[0];
    Card playerCardTwo = deck[1];
    playerCards.push_back(playerCardOne);
    playerCards.push_back(playerCardTwo);
    std::cout << playerCardOne << " " << playerCardTwo << std::endl;

    std::cout << "Its your turn!!! \nHow Much Would you Like To Bet?";
    std::cout << "\n----List of Moves---- \n 1.) Hit \n 2.) Stand \n 3.) Double Down \n";
    std::cout << "\n Please Enter the Number For Your Move: ";
    
    //This part turns the playersn number to the Enum that is represented by their move
    int move;
    std::cin >> move;
    //This converts the move to a type of the enum I made in game.h when the code compiles
    playerOptions playerMove = static_cast<playerOptions>(move - 1);

    if(playerMove == HIT){
        std::cout << "You Get A New Card" << std::endl;
        Card playerCardThree = deck[cardIndex];
        cardIndex += 1;
        std::cout << "Here is Your New Card: " << playerCardThree << std::endl;
        playerCards.push_back(playerCardThree);
    } else if (playerMove == STAND){
        std::cout << "You Stand With Your Cards" << std::endl;
    } else if(playerMove == DOUBLEDOWN) {
        std::cout << "You double your bet, and get Another Card" << std::endl;
        Card playerCardThree = deck[cardIndex];
        cardIndex += 1;
        std::cout << "Here is Your New Card: " << playerCardThree << std::endl;
        playerCards.push_back(playerCardThree);
    }
    Game::computerTurn(deck);
}

void Game::computerTurn(Deck& deck){
    std::cout << "Its now the dealers turn" << std::endl;
    Card computerCardUp = deck[cardIndex];
    cardIndex++;
    computerCards.push_back(computerCardUp);
    Card computerCardDown = deck[cardIndex];
    cardIndex++;
    computerCards.push_back(computerCardDown);
    std::cout << "Heres one of the Computer Cards: " << computerCardUp << std::endl;
    checkRound();
}

void Game::checkRound(){
    std::cout << "In Total Heres all the Player Cards" << std::endl;
    for (Card card: playerCards){
        std::cout << card << "\n";
    }
    std::cout << "In Total Heres all the Computers Cards" << std::endl;
    for (Card card: computerCards){
        std::cout << card << "\n";
    }
}

void Game::endOfGame(){

}

