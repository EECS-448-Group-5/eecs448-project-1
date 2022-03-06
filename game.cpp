/**------------------------------------------------------------------------
 * @file : game.cpp
 * @author : Eric Zhuo
 * @assignment : EECS448 - Project 1
 * @brief : Game classes that uses methods from board ship and game
 *          header files to implement methods to use for the Battleship game
 * @date: 02-10-21
 *
 ------------------------------------------------------------------------ **/
#include "game.h"
#include "ship.h"
#include "board.h"
#include "Opponent.h"

Game::Game()
{
	player1_Board = new Board();
	player1_eBoard = new Board();
	player2_Board = new Board();
	player2_eBoard = new Board();
}

void Game::shipPlacement(Opponent* player1, Opponent* player2)
{

	while (numShips > 5 || numShips < 1)
	{
		std::cout << "\n";
		std::cout << "===============================================\n";
		std::cout << "Enter a number of ships from 1 to 5: ";
		std::cin >> numShips;
		if (numShips > 5 || numShips < 1)
		{
			std::cin.clear();					//Prompts for input if user gives a non integer
			std::cin.ignore();
			std::cout << "Invalid number of ships. Try again.\n";
			std::cin >> numShips;
		}
		std::cout << "===============================================\n";
	}

	std::cout << "Player 1 placing ships...\n";
	player1_ships = new Ship*[numShips];
	player1->placeShips(numShips, player1_ships, player1_Board);

	std::cout << "Player 2 placing ships...\n";
	player2_ships = new Ship*[numShips];
	player2->placeShips(numShips, player2_ships, player2_Board);
}

void Game::fire(Opponent* player, int playerNum)
{
	if (playerNum == 1)
	{
		player->makeMove(player2_Board, player2_ships, numShips, player1_eBoard);
	}
	else
	{
		player->makeMove(player1_Board, player1_ships, numShips, player2_eBoard);
	}
}

//assumes the game has already ended, and one player has won.
bool Game::player1Won()
{
    for(int i=0;i<numShips;i++) //for loops for the amount of ships in the game
    {
        if(player1_ships[i]->is_sunk()==false) //if one of player 1's ships has not been sunk
            {
                player1WonCheck = true; //tells the game that player 1 has won
            }
    }
    return player1WonCheck; //returning the true false statement
}

bool Game::gameEndCheck()
{
	bool player1_end = true;
	bool player2_end = true;

    for(int i=0;i<numShips;i++) //loops to check for ship index sunk status
    {
        if(player1_ships[i]->is_sunk() == false) //continues the game if all ships are not sunk from player 1
        {
            player1_end = false;
			break;
        }
		}
		for(int i=0;i<numShips;i++)
		{
			if(player2_ships[i]->is_sunk()==false)//continues the game if all ships are not sunk from player 2
        	{
          		player2_end = false;
				break;
        	}
		}
 	return(player1_end || player2_end); //return either the player 1 and 2 boolean
}
Game::~Game()
{
  	for (int i=0; i<numShips; i++) //deletes all indexes of ships
	{
		delete player1_ships[i];
		delete player2_ships[i];
	}
	delete[] player1_ships; //delete the pointer of ship 1
	delete[] player2_ships;//delete the pointer of ship 2

}
