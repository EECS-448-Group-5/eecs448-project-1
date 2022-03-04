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

	std::cout << "Player 2 placing ships...\n";
	player2_ships = new Ship*[numShips];


	player1->placeShips(numShips, player1_ships, player1_Board);
	player2->placeShips(numShips, player2_ships, player2_Board);
}

void Game::fire(Opponent* player, int playerNum)
{
	if (playerNum == 1)
	{
		player->makeMove(player1_eBoard, player2_ships, numShips, player1_eBoard);
	}
	else
	{
		player->makeMove(player2_eBoard, player1_ships, numShips, player2_eBoard);
	}
	
	/*
	int shotSelection = 0;
	
    //checks user input
    char col = 'A';
    int newCol = 0;
    int row = 0;
    int missCount = 0;

	std::cout << "===============================================\n";
    std::cout << "Player: " << playerName << "\nEnter Coordinate to Attack\n(letters a-j for column and 0-9 for rows\n(example column: a and row: 2 = a2)):\n";
	std::cout << "===============================================\n";

    do
    {
		std::cin.clear();	//Prompts for input if user gives a non character
		std::cin.ignore();
    	std::cout << "Column: ";
    	std::cin >> col;
    	col=tolower(col); //change user input char to always lowercase
    	newCol = col; //set char col to int newCol 
    	newCol = newCol - 97; //converts it to 0-9 based on ascii value
    	result =(newCol<=9 && newCol >=0); //checks for the converted ascii value to see if its 0=9 for a-j
    	if(result == false)
    	{
      	std::cout << "Invalid input. Please enter letters a-j.";
    	}
    }
		while (result == false);  //only accept user input a-j

    do
    {
		std::cin.clear();	//Prompts for input if user gives a non integer
		std::cin.ignore();
	    std::cout << "Row: ";
	    std::cin >> row;
	    result =(row<=10 && row >=1); //check user input to see if its between 1-10
	    if(result == false)
	    {
	          std::cout << "Invalid input. Please enter numbers 1-10.";
	    }
    }
		while (result == false); //only accept user input 1-10

		if(playerName=="Player 1")
    {
    	missCount=0;
			for(int i=0;i<numShips;i++)
 			{
    		try
    		{
      		player2_ships[i]->hit(col, row); //check location of ship index and throws if the ship is not at location against player 2's placed ships
    		}
    		catch(const std::exception& e)
    		{
	        missCount++; //increments a counter for misses (1 ship selected = 1 at a specific location and so on...)
    		}
			}
    	if(numShips==missCount) //if misses equals to the ship index it would mark the specific location with M for miss
    	{
		std::cout << "\nMISS!\n";
      	player1_eBoard.updateBoard(col,row,missChar);
    	}
		else
    	{
			std::cout << "\nHIT!\n";
      	player1_eBoard.updateBoard(col,row,hitChar); //if the miss counter is not incremented it would mark with * for hit
    	}

			std::cout << "===============================================\n";
    	std::cout << "Player 1's board\n" ;
    	player1_Board.printBoard();
    	std::cout << "\nEnemy's Board\n" ;
    	player1_eBoard.printBoard();
			std::cout << "===============================================\n";
    }

		if(playerName=="Player 2")
    {
	    missCount= 0;
			for(int i=0;i<numShips;i++)
    	{
	    	try
	    	{
	       player1_ships[i]->hit(col, row);//check location of ship index and throws if the ship is not at location against player 1's placed ships
	    	}
	    	catch(const std::exception& e)
	    	{
	        missCount++; //increments a counter for misses (1 ship = 1 at a specific location and so on...)
	    	}
			}
		if(numShips==missCount)
	    {
			std::cout << "\nMISS!\n";
	      player2_eBoard.updateBoard(col,row,missChar); //if misses equals to the ship index it would mark the specific location with M for miss
	    }
	    else
	    {
			std::cout << "\nHIT!\n";
	      player2_eBoard.updateBoard(col,row,hitChar); //if the miss counter is not incremented it would mark with * for hit
	    }
			std::cout << "===============================================\n";
			std::cout << "Player 2's board\n";
	    player2_Board.printBoard();
	    std::cout << "Enemy's Board\n" ;
	    player2_eBoard.printBoard();
			std::cout << "===============================================\n";
  	}
	  */
}

bool Game::player1Won()
{
    for(int i=0;i<numShips;i++) //for loops for the amount of ships in the game
    {
        if(player1_ships[i]->is_sunk()==true) //checks the status of the ship if it marked with *
            {
                player1WonCheck = false; //tells the game that player 1 has lost
            }
            else
            {
                player1WonCheck = true;//the game ends with player 2 winning
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
