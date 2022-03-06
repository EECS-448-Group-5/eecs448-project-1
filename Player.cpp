#include "Player.h"

Player::Player()
{

}

void Player::makeMove(Board* enemyBoard, Ship** enemyShips, int numShips, Board* guessBoard)
{
    std::cout << "===============================================\n";
    std::cout << "Your board\n" ;
    homeBoard->printBoard();
    std::cout << "\nEnemy's Board\n" ;
    guessBoard->printBoard();
	std::cout << "===============================================\n";


    int shotSelection = 0;
    std::string shotType;
	char col = 'A';
    int newCol = 0;
    int row = 0;
    int missCount = 0;
    bool result = false;

    std::cout << "Enter shot type (normal: inf, | bomb: " << bombShotCount << " | consecutive: " << consecutiveShotCount << " | random: " << randomShotCount << "): ";
    std::cin >> shotType;

    while ( std::cin.fail() || ( shotType != "n" && shotType != "normal" && 
                               (shotType != "bomb" && shotType != "b" || bombShotCount == 0) && 
                               (shotType != "consecutive" && shotType != "c" || consecutiveShotCount == 0) && 
                               (shotType != "random" && shotType != "r" || randomShotCount == 0)) )
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		std::cout << "\n";
		std::cout << "Invalid selection. Please input normal, bomb, consecutive, or random: ";
		std::cin >> shotType;
	}

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    //if they're doing a random shot, we don't need to ask for coordinates.
    if(shotType == "random" || shotType == "r"){
        randomShot(enemyBoard, enemyShips, numShips, guessBoard);
    }else{

        do
        {
            //get input coordinates
        	std::cout << "===============================================\n";
            std::cout << "Enter Coordinate to Attack\n(letters a-j for column and 0-9 for rows\n(example column: a and row: 2 = a2)):\n";
        	std::cout << "===============================================\n";

            do
            {
        		std::cin.clear();	//Prompts for input if user gives a non character
        		//std::cin.ignore();
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

            do
            {
        		std::cin.clear();	//Prompts for input if user gives a non character
        		std::cin.ignore();
            	std::cout << "Row: ";
            	std::cin >> row;
            	result = (row<=10 && row >=1); //checks for the converted ascii value to see if its 0=9 for a-j
            	if(result == false)
            	{
              	    std::cout << "Invalid input. Please enter letters a-j.";
            	}
            }
        	while (result == false);  //only accept row input 1-10

        }
        while ((shotType == "c" || shotType == "consecutive") && 
                consecutiveShot(enemyBoard, enemyShips, numShips, guessBoard, row, col));
        //always get coords once, then repeatedly get new coords each time there is a successful consecutive shot.
        //NOTE: will not call consecutiveShot if the first line evaluates to false


        if(shotType == "b" || shotType == "bomb"){
            bombShot(enemyBoard, enemyShips, numShips, guessBoard, row, col);
        }else if(shotType == "n" || shotType == "normal"){
            //normal shot

            for(int i=0; i<numShips; i++){
                try{
                    enemyShips[i]->hit(col, row);
                }catch(std::exception& e){

                }
            }

            if(!enemyBoard->isValidSpace(col - 97, row-1))
            {
                std::cout << "\nHIT!\n";
                guessBoard->updateBoard(col, row, '*');
            }
            else
            {
                std::cout << "\nMISS!\n";
                guessBoard->updateBoard(col, row, 'M');
            }
        }

    }
}

void Player::placeShips(int numShips, Ship** shipList, Board* homeBoard)
{
    this->homeBoard = homeBoard;
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
                invalid = 1;
            }
        }
    }
}
//bomb shot will hit a 3x3 with the center being the col and row passed as the parameter
void Player::bombShot(Board* enemyBoard, Ship** enemyShips, int numShips, Board* guessBoard, int row, char col){
    bombShotCount--;
    //hit the 9 squares
    for(int r = row-1; r <= row+1; r++){
        for(int c = col-1; c <= col+1; c++){
            //if the tile is off the board, do nothing.
            if(r==0 || r==11 || c==96 || c==107) continue;

            //let each ship update if they've been hit/sunk
            for(int i=0; i<numShips; i++){
                try{
                    enemyShips[i]->hit(c, r);
                }catch(std::exception& e){}
            }

            if(!enemyBoard->isValidSpace(c-97, r-1)){
                guessBoard->updateBoard(c, r, '*');
            }else{
                guessBoard->updateBoard(c, r, 'M');
            }
        }
    }

}

bool Player::consecutiveShot(Board* enemyBoard, Ship** enemyShips, int numShips, Board* guessBoard, int row, char col){
    
    for(int i=0; i<numShips; i++){
        try{
            enemyShips[i]->hit(col, row);
        }catch(std::exception& e){

        }
    }

    if(!enemyBoard->isValidSpace(col - 97, row-1))
    {
            guessBoard->updateBoard(col, row, '*');
            return true;
    }

    //only decrement ammo when they miss (so it only decrements once per consecutive shot)
    consecutiveShotCount--;

    guessBoard->updateBoard(col, row, 'M');
    return false;
}
void Player::randomShot(Board* enemyBoard, Ship** enemyShips, int numShips, Board* guessBoard){
    randomShotCount--;
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

