#include <iostream>
#include "game.h"
#include "deck.h"

Game::Game() { 
    int cardIndex = 2;
}

void Game::startGame(Deck& deck){
    std::cout << "Welcome To Jack Black" << std::endl;
}

//This Function Checks to see what bet you place before the game Fully Starts. 
void Game::startOfRound(){
    int playerMoney = 100;
    int betMoney = 0;
    std::cout << "Your Current Amount of Money is " << playerMoney << "!!!\nPlease Enter how Much You Would Like To Bet:";
    std::cin >> betMoney;
    if(betMoney > playerMoney){
        std::cout << "This Bet is more than you have Please Enter an amount Less than" << playerMoney << std::endl;
        startOfRound();
    } else {
        int finalBet = betMoney;
    }
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

