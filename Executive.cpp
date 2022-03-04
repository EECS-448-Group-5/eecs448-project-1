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

Executive::Executive()
{
}

void Executive::play()
{
	Game gameFunction;               //initializes the game logic object

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
		gameFunction.fire(player1, 1);
		//then asks player two for a move
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

Opponent* Executive::selectPlayer(std::string player)
{
	std::string playerType = "";
	std::string difficulty = "";
	Opponent* opponent = nullptr;
	
	std::cout << "\n";
	std::cout << "Please specify who " << player << " is (human/computer): ";
	std::cin >> playerType;

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

	if (playerType == "h")
	{
		opponent = new Player();
	}
	else if (playerType == "computer" || playerType == "c")
	{
		std::cout << "\n";
		std::cout << "Please select the difficulty (easy/medium/hard): ";
		std::cin >> playerType;

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

		if (playerType == "e")
		{
			opponent = new EasyAI();
		}
		else if (playerType == "m")
		{
			opponent = new MediumAI();
		}
		else if (playerType == "h")
		{
			opponent = new HardAI();
		}
	}

	return (opponent);
}

Executive::~Executive()
{
}