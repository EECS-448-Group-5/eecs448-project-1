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
     if(!enemyBoard->isValidSpace(col - 97, row))
    {
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
void Player::randomShot(Board* enemyBoard, Ship** enemyShips, int numShips, Board* guessBoard, int row, char col){
    
}

