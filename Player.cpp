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
void Player::consecutiveShot(Board* enemyBoard, Ship** enemyShips, int numShips, Board* guessBoard, int row, char col){
   
}
void Player::randomShot(Board* enemyBoard, Ship** enemyShips, int numShips, Board* guessBoard, int row, char col){
   
}

