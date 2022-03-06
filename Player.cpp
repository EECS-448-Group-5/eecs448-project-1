#include "Player.h"

Player::Player()
{

}

void Player::makeMove(Board* enemyBoard, Ship** enemyShips, int numShips, Board* guessBoard)
{
    int shotSelection = 0;
    std::string shotType;
	char col = 'A';
    int newCol = 0;
    int row = 0;
    int missCount = 0;
    bool result = false;

    std::cout << "Enter shot type (normal: inf, | bomb: " << bombShotCount << " | consecutive: " << consecutiveShotCount << " | random: " << randomShotCount << "): ";
    std::cin >> shotType;

    while ( std::cin.fail() || ( shotType != "bomb" && shotType != "b" && shotType != "consecutive" && shotType != "c" && shotType != "random" && shotType != "r") )
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		std::cout << "\n";
		std::cout << "Invalid selection. Please input bomb, consecutive, or random: ";
		std::cin >> shotType;
	}

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::cout << "===============================================\n";
    std::cout << "Enter Coordinate to Attack\n(letters a-j for column and 0-9 for rows\n(example column: a and row: 2 = a2)):\n";
	std::cout << "===============================================\n";

    do
    {
		std::cin.clear();	//Prompts for input if user gives a non character
		std::cin.ignore();
    	std::cout << "Column: ";
    	std::cin >> col;
    	col = tolower(col); //change user input char to always lowercase
    	newCol = col; //set char col to int newCol 
    	newCol = newCol - 97; //converts it to 0-9 based on ascii value
    	result = (newCol<=9 && newCol >=0); //checks for the converted ascii value to see if its 0=9 for a-j
    	if(result == false)
    	{
      	    std::cout << "Invalid input. Please enter letters a-j.";
    	}
    }
	while (result == false);  //only accept user input a-j

/*

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
  	} */
}

void Player::placeShips(int numShips, Ship** shipList, Board* homeBoard)
{
    for (int i = 0; i < numShips; i++)
    {
        int invalid = 1;

        while (invalid != 0)
        {
            try
            {
                char col = 'A';
                int newCol = 0;
                int row = 0;
                char direction = 'a';
                bool result = true;

                std::cout << "===============================================\n";
                std::cout << "Where would you like to place ship " << i+1 << "?\n";

                do
                {
                    std::cin.clear();					//Prompts for input if user gives a non integer
                    std::cin.ignore();
                    std::cout << "Column: ";
                    std::cin >> col;
                    col = tolower(col);
                    newCol = col;
                    newCol = newCol - 97;
                    result = (newCol <= 9 && newCol >= 0);
                    if (result == false)
                    {
                        std::cout << "Invalid input. Please enter letters a-j.";
                    }
                }
                while (result == false);

                do
                {
                    std::cin.clear();					//Prompts for input if user gives a non integer
                    std::cin.ignore();
                    std::cout << "Row: ";
                    std::cin >> row;
                    result = (row <= 10 && row >= 1);
                    
                    if (result == false)
                    {
                        std::cout << "Invalid input. Please enter numbers 1-10.";
                    }
                }
                while (result == false);

                do
                {
                    std::cout << "Direction: ";
                    std::cin >> direction;
                    result = (direction == 'v' || direction == 'h');

                    if(result == false)
                    {
                        std::cout << "Invalid input. please enter v(ertical) or h(orizonal)";
                    }
                }
                while (result == false);
                
                std::cout << "===============================================\n";

                shipList[i] = new Ship(i + 1, direction, col, row);
                homeBoard->placeShip(shipList[i]);

                invalid = 0;
            }
            catch(std::exception& e)
            {
                std::cout << e.what() << '\n';
                invalid++;
            }
        }
    }
}
//bomb shot will hit a 3x3 with the center being the col and row passed as the parameter
void Player::bombShot(Board* enemyBoard, Ship** enemyShips, int numShips, Board* guessBoard, int row, char col){
    //hit the 9 squares
    for (int i = 0; i < numShips; i++){
        try{
            //spot 1
            enemyShips[i]->hit(col-1,row -1);
            //spot 2
            enemyShips[i]->hit(col,row -1);
            //spot 3
            enemyShips[i]->hit(col+1,row-1);
            //spot 4
            enemyShips[i]->hit(col-1,row);
            //spot 5
            enemyShips[i]->hit(col,row);
            //spot 6
            enemyShips[i]->hit(col+1,row);
            //spot 7
            enemyShips[i]->hit(col-1,row+1);
            //spot 8
            enemyShips[i]->hit(col,row+1);
            //spot 9
            enemyShips[i]->hit(col+1,row+1);

        }
        catch(const std::exception& e){
            std::cerr << e.what() << '\n';
        }
        
    }
    //update board
     if(!enemyBoard->isValidSpace(col - 97, row)){
            guessBoard->updateBoard(col-1, row-1, '*'); //1
            guessBoard->updateBoard(col,row -1, '*'); //2
            guessBoard->updateBoard(col+1,row-1, '*');//3
            guessBoard->updateBoard(col-1,row, '*');//4
            guessBoard->updateBoard(col, row, '*');//5
            guessBoard->updateBoard(col+1,row, '*');//6
            guessBoard->updateBoard(col-1,row+1, '*');//7
            guessBoard->updateBoard(col,row+1, '*');//8
            guessBoard->updateBoard(col+1,row+1, '*');//9
            
    }

    guessBoard->updateBoard(col-1, row-1, 'M'); //1
    guessBoard->updateBoard(col,row -1, 'M'); //2
    guessBoard->updateBoard(col+1,row-1, 'M');//3
    guessBoard->updateBoard(col-1,row, 'M');//4
    guessBoard->updateBoard(col, row, 'M');//5
    guessBoard->updateBoard(col+1,row, 'M');//6
    guessBoard->updateBoard(col-1,row+1, 'M');//7
    guessBoard->updateBoard(col,row+1, 'M');//8
    guessBoard->updateBoard(col+1,row+1, 'M');//9
bombShotCount--;
}

bool Player::consecutiveShot(Board* enemyBoard, Ship** enemyShips, int numShips, Board* guessBoard, int row, char col){
      for(int i=0; i<numShips; i++){
        try{
            enemyShips[i]->hit(col, row);
        }catch(std::exception& e){

        }
    }

    if(!enemyBoard->isValidSpace(col - 97, row))
    {
            guessBoard->updateBoard(col, row, '*');
            return true;
    }

    guessBoard->updateBoard(col, row, 'M');
    return false;
}
void Player::randomShot(Board* enemyBoard, Ship** enemyShips, int numShips, Board* guessBoard){
    for(int i = 0; i<3; i++){
        srand(time(NULL));
        int col = 0;
        int row = 0;
        do {
            col = rand() % 10; //to make random guess, obtain two random numbers between 0 and 9 (inputs to board array)
            row = rand() % 10;
        }
        while(!guessBoard->isValidSpace(col, row)); //while conditions controls for repeat guesses
    
        col = col + 97;
        char col_char = col; //transform the column number into its ASCII equivalent so other functions recognize it
        col = col - 97;
    
        for(int i=0; i<numShips; i++){
            try{
                enemyShips[i]->hit(col_char, row+1);
            }catch(std::exception& e){

        }
    }
    if(!enemyBoard->isValidSpace(col, row)) { //update the guessed board
        guessBoard->updateBoard(col_char, row+1, '*');
    }
    else {
        guessBoard->updateBoard(col_char, row+1, 'M');
    }
    }
}

