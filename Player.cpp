#include "Player.h"

Player::Player()
{

}

void Player::makeMove(Board* enemyBoard, Ship** enemyShips, int numShips, Board* guessBoard)
{

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
void Player::bombShot(Board* enemyBoard, Ship** enemyShips, int numShips, Board* guessBoard, int row, char col){
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
    srand(time(NULL));
    int row = 0;
    int col = 0;
    do {
        col = rand() % 10; //to make random guess, obtain two random numbers between 0 and 9 (inputs to board array)
        row = rand() % 10;
    }
    while(!guessBoard->isValidSpace(col, row)); //while conditions controls for repeat guesses
    
    col = col + 97;
    char col_char = col; //transform the column number into its ASCII equivalent so other functions recognize it
    col = col - 97;

    for(int i=0; i<numShips; i++) { //informs the ship arrays whether they'll be hit or not
        enemyShips[i]->hit(col_char, row);
    }

    if(!enemyBoard->isValidSpace(col, row)) { //update the guessed board
        guessBoard->updateBoard(col_char, row, '*');
    }
    else {
        guessBoard->updateBoard(col_char, row, 'M');
    }
}

