#include <iostream>
#include "game.h"
#include "deck.h"
#include <random>

Game::Game() { 
    /*for future refrence doing something like
    int cardIndex; makes it sso the cardIndex is local and resets its value in a way*/
    //cardIndex;
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

    std::cout << "\n\n Now the Dealer will get there cards" << std::endl;
    //This gives us an idea of what the computers cards are before the player choose their moves
    Game::comCards(deck);

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

void Game::comCards(Deck& deck){
    //This parts getting the dealers or the computers cards for them. 
    std::cout << "Its now the dealers turn" << std::endl;
    Card computerCardUp = deck[cardIndex];
    cardIndex++;
    computerCards.push_back(computerCardUp);
    Card computerCardDown = deck[cardIndex];
    cardIndex++;
    computerCards.push_back(computerCardDown);
    std::cout << "Heres one of the Dealer Cards: " << computerCardUp << std::endl;

}

void Game::computerTurn(Deck& deck){
    /*This below code was jsut stuff when i was testing and figureout the getters and setters in C++ it can be ignored its more so for me for debugging 
    std::cout << "computer turn test" << std::endl;
    std::cout << computerCards[0] << std::endl;
    Card testCard = computerCards[0];
    int rannumb = testCard.getNumber();
    std::cout << rannumb << std::endl;
    */ 

    //Gets the numbers attached to the two cards. 
    int comCardNumUno = computerCards[0].getNumber();
    int comCardNumDos = computerCards[1].getNumber();
    std::cout << comCardNumUno << std::endl;
    std::cout << comCardNumDos << std::endl;

    int dealerSum = comCardNumDos + comCardNumUno;
    if(dealerSum <= 17){
        std::cout << "The dealer HAS to Hit!" << std::endl;
        computerCards.push_back(deck[cardIndex]);
        std::cout << computerCards[-1] << std::endl;
    } else {
        std::random_device rdDos; 
        std::mt19937 gen(rdDos()); 
        std::uniform_int_distribution<> distrib(1, 2);
        
        int dealerMove = distrib(gen);
        if(dealerMove == 1){
            std::cout << "The dealer has CHOOSEN to Hit!" << std::endl;
            computerCards.push_back(deck[cardIndex]);
            std::cout << computerCards[-1] << std::endl;
        } else if(dealerMove == 2){
            std::cout << "The Dealer Has Choosen To Stay" << std::endl;
        }
    }
    Game::checkRound();
}

void Game::checkRound(){
    int playerCardSum = 0;
    int dealerCardSum = 0;

    std::cout << "In Total Heres all the Player Cards" << std::endl;
    for (Card cardY: playerCards){
        std::cout << cardY << "\n";
        playerCardSum += cardY.getNumber();
    }
    std::cout << "In Total Heres all the Computers Cards" << std::endl;
    for (Card cardX: computerCards){
        std::cout << cardX << "\n";
        dealerCardSum += cardX.getNumber();
    }
    std::cout << "Players Cards Sum is: " << playerCardSum << "     |    Dealer Cards Sum is: " << dealerCardSum << std::endl;

    if (dealerCardSum > playerCardSum && dealerCardSum < 21){
        std::cout << "The dealer has won this ROUND" << std::endl;
    } else if (playerCardSum > dealerCardSum){
        std::cout << "The player has won this ROUND" << std::endl;
    } else if (playerCardSum == dealerCardSum){
        std::cout << "THIS ROUND IS TIED!!!" << std::endl;
    }
    Game::endOfGame();
}

void Game::endOfGame(){
    std::cout << "Update Bets Values TEST MUST DO\n";
    std::cout << "Would you like to Continute the Game? \n" << std::endl;
    std::cout << "-----Options----\n 1.) Play Again \n 2.) Quit" << std::endl;
    std::cout << "Enter Number For Option: ";
    int playerAnswer;
    std::cin >> playerAnswer; 
}

/* things left to do handle busts for player in cards choosing
Handling whether or not your or dealer is in negative money, and then forcing a quit
Handling the bets
Updating the BEts
*/
