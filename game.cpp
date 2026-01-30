#include <iostream>
#include "game.h"
#include "deck.h"
#include <random>

Game::Game(Deck& deck) : deck(deck) { 
    
}
//This is just a quick intro to the game made it easier for me to have a start like this when testing the game 
void Game::startGame(){
    std::cout << "---------Welcome To Jack Black---------\n\n" << std::endl;
    Game::placeBets();
}

/*This Function Checks to see what bet you place before the game Fully Starts. 
It also takes care of the dealers bet through random number generation I used the random generation we talked about in class 
today*/
void Game::placeBets(){
    //This is all my logic for place a bet for the human player and checking to make sure they have enough money to make the bet
    int betMoney = 0;
    std::cout << "Your Current Amount of Money is " << playerMoney << "!!!\nPlease Enter how Much You Would Like To Bet: ";
    std::cin >> betMoney;
    if(betMoney > playerMoney){
        std::cout << "This Bet is more than you have Please Enter an amount Less than" << playerMoney << std::endl;
        placeBets();
    } else {
        finalBet = betMoney;
    }
    std::cout << "------------------------------------------------\n\n" << std::endl;

    //This is the logic to deal with the dealer placing a bet
    //This random generator thing I used from the random generator that we talked about in class when showing us SDL3
    std::cout << "The Dealer has the following amount of Money: " << computerMoney << std::endl;
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distrib(1, computerMoney);

    computerBet = distrib(gen);
    std::cout << "The Dealer Places a bet of $" << computerBet << "\n\n" << std::endl;

    Game::playerTurn();
}

void Game::playerTurn(){
    std::cout << "Here are your two Cards: \n";
    Card playerCardOne = deck[0];
    Card playerCardTwo = deck[1];
    playerCards.push_back(playerCardOne);
    playerCards.push_back(playerCardTwo);
    std::cout << playerCardOne << " " << playerCardTwo << std::endl;

    //std::cout << "\n\nNow the Dealer will get there cards" << std::endl;
    //This gives us an idea of what the computers cards are before the player choose their moves
    Game::comCards();

    std::cout << "Its your turn to choose a Move!!! \n";
    std::cout << "\n-------List of Moves-------\n 1.) Hit \n 2.) Stand \n 3.) Double Down \n";
    std::cout << "\n Please Enter the Number For Your Move: ";
    
    //This part turns the playersn number to the Enum that is represented by their move
    int move;
    std::cin >> move;
    std::cout << "\n\n\n";
    //This converts the move to a type of the enum I made in game.h when the code compiles
    playerOptions playerMove = static_cast<playerOptions>(move - 1);

    if(playerMove == HIT){
        Card playerCardThree = deck[cardIndex];
        cardIndex += 1;
        std::cout << "Here is Your New Card: " << playerCardThree << std::endl;
        playerCards.push_back(playerCardThree);
    } else if (playerMove == STAND){
        std::cout << "You Stand With Your Cards" << std::endl;
    } else if(playerMove == DOUBLEDOWN) {
        std::cout << "You double your bet, and get Another Card" << std::endl;
        int doubleVertification;
        doubleVertification = (finalBet * 2); 
        if(doubleVertification < playerMoney) {
            Card playerCardThree = deck[cardIndex];
            cardIndex += 1;
            finalBet += finalBet;
            std::cout << "Here is Your New Card: " << playerCardThree << std::endl;
            playerCards.push_back(playerCardThree);
        } else {
            std::cout << "You don't have enough money to Double Down Please choose a different option :/ \n\n" << std::endl;
            Game::playerTurn(); 
        }
    }
    //Checking to see if you "BUST" immediatly after your turn?
    int playerCardSum = 0;
    for (Card cardI: playerCards){
        playerCardSum += cardI.getNumber();
    }
    std::cout << "Heres the sum of your cards: " << playerCardSum << std::endl;
    if(playerCardSum > 21){
        std::cout << "You got a bust, you lose before the dealer even has played :(" << std::endl;
        playerMoney -= finalBet; 
        computerMoney += finalBet;
        //std::cout << "You now have $" << playerMoney << " | Dealer now has $" << computerMoney << std::endl;
        if(playerMoney <= 0){
            std::cout << "You have no more money to bet sorry but you lose for now :(\n" << std::endl;
        } 
        std::cout << "Since You Got a Bust This round ends immedietly" << std::endl;
        Game::endOfGame();
    } else {
        Game::computerTurn();
    }

}

void Game::comCards(){
    //This parts getting the dealers or the computers cards for them. 
    std::cout << "\n\nNow the dealer is getting their cards" << std::endl;
    Card computerCardUp = deck[cardIndex];
    cardIndex++;
    computerCards.push_back(computerCardUp);
    Card computerCardDown = deck[cardIndex];
    cardIndex++;
    computerCards.push_back(computerCardDown);
    std::cout << "Heres one of the Dealer Cards: " << computerCardUp << "\n\n" << std::endl;

}

void Game::computerTurn(){
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
            std::cout << "The dealer has CHOOSEN to Hit!\n" << std::endl;
            computerCards.push_back(deck[cardIndex]);
            std::cout << computerCards[-1] << std::endl;
        } else if(dealerMove == 2){
            std::cout << "The Dealer Has Choosen To Stay\n" << std::endl;
        }
    }
    Game::checkForBlackjack();
}

//This funciton helps summarize what cards you and the dealer have and ten gets the results for who won that round of the game 
void Game::checkRound(){
    int playerCardSum = 0;
    int dealerCardSum = 0;

    std::cout << "\n\nIn Total Heres all the Player Cards" << std::endl;
    for (Card cardY: playerCards){
        std::cout << cardY << " ";
        playerCardSum += cardY.getNumber();
    }
    std::cout << "\n---------------------------------\n\n\nIn Total Heres all the Computers Cards" << std::endl;
    for (Card cardX: computerCards){
        std::cout << cardX << " ";
        dealerCardSum += cardX.getNumber();
    }
    std::cout << "\n\nPlayers Cards Sum is: " << playerCardSum << "     |    Dealer Cards Sum is: " << dealerCardSum << std::endl;

    if (dealerCardSum > playerCardSum && dealerCardSum < 21){
        std::cout << "The dealer has won this ROUND" << std::endl;
        playerMoney -= finalBet; 
        computerMoney += finalBet;
    } else if (playerCardSum > dealerCardSum || dealerCardSum > 21){
        std::cout << "The player has won this ROUND" << std::endl;
        playerMoney += computerBet;
        computerMoney -= computerBet;
    } else if (playerCardSum == dealerCardSum){
        std::cout << "THIS ROUND IS TIED!!!" << std::endl;
    }
    Game::endOfGame();
}

//This funciton is supposed to check if a jackblack is in one of the players hands. 
void Game::checkForBlackjack(){
    bool phasBJ = false; 
    bool chasBJ = false ;
    if (playerCards.size() == 2 && ((playerCards[0].getNumber() == 10 && playerCards[1].getNumber() == 1) ||(playerCards[0].getNumber() == 1 && playerCards[1].getNumber() == 10))){
        phasBJ = true;
    }
    if (computerCards.size() == 2 && ((computerCards[0].getNumber() == 10 && computerCards[1].getNumber() == 1) ||(computerCards[0].getNumber() == 1 && computerCards[1].getNumber() == 10))){
        chasBJ = true;
    }

    if (phasBJ == true && chasBJ == false ){
        playerMoney += computerBet;
        computerMoney -= computerBet;
        std::cout << "Player Has a Blackjack they win this round!!\n\n";
        Game::endOfGame();
    } else if (phasBJ == false && chasBJ == true){
        playerMoney -= finalBet; 
        computerMoney += finalBet;
        std::cout << "Dealer Has a Blackjack they win this round!!\n\n";
        Game::endOfGame();
    } else if (phasBJ == true && chasBJ == true){
        std::cout << "Both Playersr have a blackjack This round ends no one loses money :) \n\n";
        Game::endOfGame();
    } else {
        Game::checkRound();
    }
}

//This function helps give a summary of what happened to the game, and then  helps reset the values whether you choose to conintue the game, and then lets you choose to quit the game 
void Game::endOfGame(){
    std::cout << "You now have $" << playerMoney << " | Dealer now has $" << computerMoney << std::endl;
    if (playerMoney <= 0 || computerMoney <= 0){
        std::cout << "Someone has no more money to play with :(\n\n --------The game Must End :/ -------";
        std::exit(0);
    }

    std::cout << "Would you like to Continute the Game? \n" << std::endl;
    std::cout << "-----Options----\n 1.) Play Again \n 2.) Quit" << std::endl;
    std::cout << "Enter Number For Option: ";
    int playerAnswer;
    std::cin >> playerAnswer; 
    if(playerAnswer == 1){
        std::cout << "YOU CHOOSE TO PLAY AGAIN DON'T LOSE YOUR MONEY \n\n";
        //Resetting the Values: 
        playerCards.clear();
        computerCards.clear();
        cardIndex = 2;
        finalBet = 0;
        computerBet = 0;
        Deck::shuffle(deck);
        Game::startGame();
    } else if (playerAnswer == 2){
        std::cout << "YOU HAVE CHOOSEN TOO QUIT, WHATS BETTER THAN GAMBLING THOO!!!! :(   --bye bye\n\n";
    } else {
        std::cout << "You options are only 1, and 2 please try again :(" << std::endl;
        Game::endOfGame();
    }
}

/* things left to do handle busts for player in cards choosing
Handling whether or not your or dealer is in negative money, and then forcing a quit
Handling the bets
Updating the BEts
*/
