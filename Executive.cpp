/** ------------------------------------------------------------------------
 * @file : Executive.cpp
 * @author : Aidan Bowen
 * @assignment : EECS448 - Project 1
 * @brief : Class that runs the game and uses methods implemented by other
			classes to control the functions of the game
 * @date: 02-06-21
 *
 ------------------------------------------------------------------------ **/
#include "Executive.h"
#include "board.h"
#include "ship.h"
#include "game.h"
#include "Player.h"
#include "EasyAI.h"
#include "MediumAI.h"
#include "HardAI.h"
#include <stdexcept>
#include <iostream>
#include <string>
#include <stdlib.h>

Executive::Executive()
{
}

void Executive::play()
{
	Game gameFunction;               //initializes the game logic object

	srand(time(NULL));
	std::cout << "\n";
	std::cout << "===============================================\n";
	std::cout << "Welcome to Battleship!\n";
	std::cout << "===============================================\n";

	Opponent* player1 = selectPlayer("Player 1");
	Opponent* player2 = selectPlayer("Player 2");

	gameFunction.shipPlacement(player1, player2);
	
	//starts game by looping until game over is true
	do
	{
		//asks player one for a move
		std::cout<< "================================================\n"
				 << "Player 1 Turn\n"
				 << "================================================\n";
		gameFunction.fire(player1, 1);
		//then asks player two for a move
		std::cout<< "================================================\n"
				 << "Player 2 Turn\n"
				 << "================================================\n";
		gameFunction.fire(player2, 2);
	} while (gameFunction.gameEndCheck() == false);   //checks if game is over and ends the loop if true

	if (gameFunction.player1Won()==true)
	{
    	std::cout << "===============================================\n";
		std::cout << "Game over!\n";
		std::cout << "Player1 has won!\n";
    	std::cout << "===============================================\n";
	}
	else
	{
    	std::cout << "===============================================\n";
		std::cout << "Game over!\n";
		std::cout << "Player2 has won!\n";
    	std::cout << "===============================================\n";
	}
}

//Prompts user to select the type of player for Player 1 or Player 2 (specified by the player parameter
//which should be "Player 1" or "Player 2") and returns a pointer to an object of a subclass of Opponent.
Opponent* Executive::selectPlayer(std::string player)
{
	std::string playerType = "";
	std::string difficulty = "";
	Opponent* opponent = nullptr;
	
	//Obtains user input for player type and stores in playerType
	std::cout << "\n";
	std::cout << "Please specify who " << player << " is (human/computer): ";
	std::cin >> playerType;

	//Makes sure user input is valid.
	while ( std::cin.fail() || ( playerType != "human" && playerType != "h" && playerType != "computer" && playerType != "c" ) )
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		std::cout << "\n";
		std::cout << "Invalid selection. Please input human or computer.\n";
		std::cout << "\n";
		std::cout << "Please specify who " << player << " is (human/computer): ";
		std::cin >> playerType;
	}

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	//Creates an object of the appropriate subclass of Opponent based on user input.
	if (playerType == "h")
	{
		opponent = new Player();
	}
	else if (playerType == "computer" || playerType == "c")
	{
		//Obtains user input for difficulty of AI player.
		std::cout << "\n";
		std::cout << "Please select the difficulty (easy/medium/hard): ";
		std::cin >> playerType;

		//Ensures user input is valid.
		while ( std::cin.fail() || ( playerType != "easy" && playerType != "e" && playerType != "medium" && playerType != "m" && playerType != "hard" && playerType != "h" ) )
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			std::cout << "\n";
			std::cout << "Invalid selection. Please input easy, medium, or hard.\n";
			std::cout << "\n";
			std::cout << "Please select the difficulty (easy/medium/hard): ";
			std::cin >> playerType;
		}

    	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		//Creates an object of the appropriate subclass of Opponent.
		if (playerType == "e" || playerType == "easy")
		{
			opponent = new EasyAI();
		}
		else if (playerType == "m" || playerType == "medium")
		{
			opponent = new MediumAI();
		}
		else if (playerType == "h" || playerType == "hard")
		{
			opponent = new HardAI();
		}
	}

	return (opponent);
}

Executive::~Executive()
{
}