#include "MediumAI.h"

MediumAI::MediumAI()
{
    lastHitRow = 0;
    lastHitCol = '?';
    shipDirection = '?';
    guessDirection = 'u';
    guessDistance = 1;
}

bool MediumAI::makeGuess(char col, int row, Board* enemyBoard, Ship** enemyShips, int numShips, Board* guessBoard)
{
    for(int i=0; i<numShips; i++){
        enemyShips[i]->hit(col, row);
    }


    if(!enemyBoard->isValidSpace(col, row))
    {
            guessBoard->updateBoard(col, row, '*');
            return true;
    }

    guessBoard->updateBoard(col, row, 'M');
    return false;
}

bool MediumAI::isValidGuess(char col, int row, Board* guessBoard)
{
    return col >= 97 && col <= 106 && 
           row >= 1 && row <= 10 && 
           guessBoard->isValidSpace(row, col);
}

void MediumAI::makeMove(Board* enemyBoard, Ship** enemyShips, int numShips, Board* guessBoard)
{
    if(lastHitRow == 0)
    {//don't know where a ship is
        int guess[2] = {97,0};//getRandomGuess() TODO impl

        //if the random guess is a hit, make a note of where the hit was.
        if(makeGuess(guess[0], guess[1], enemyBoard, enemyShips, numShips, guessBoard))
        {
            lastHitRow = guess[1];
            lastHitCol = guess[0];
            guessDirection = 'u';
        }
    }
    else
    {//knows where a ship is
        if(shipDirection == '?')
        {//but doesn't know which direction it faces

            int guess[2] = {lastHitCol, lastHitRow};

            if(guessDirection == 'u')
            {
                guess[1] = lastHitRow - guessDistance;
                if(!isValidGuess(guess[0], guess[1], guessBoard))
                {//if the guess is invalid, go ahead and guess to the right instead.
                    guessDirection = 'r';
                }
            }

            if(guessDirection == 'r')
            {
                guess[0] = lastHitCol + guessDistance;
                if(!isValidGuess(guess[0], guess[1], guessBoard))
                {//if the guess is invalid, go ahead and guess down instead.
                    guessDirection = 'd';
                }
            }

            if(guessDirection == 'd')
            {
                guess[1] = lastHitRow + guessDistance;
                if(!isValidGuess(guess[0], guess[1], guessBoard))
                {//if the guess is invalid, go ahead and guess to the left instead.
                    guessDirection = 'l';
                }
            }

            if(guessDirection == 'l')
            {
                guess[0] = lastHitCol - guessDistance;
                if(!isValidGuess(guess[0], guess[1], guessBoard))
                {//at this point, we're out of directions to guess, so we must have sunk the 1x1, and should make a random move.
                    guessDirection = 'u';
                    lastHitCol = '?';
                    lastHitRow = 0;
                    makeMove(enemyBoard, enemyShips, numShips, guessBoard);
                    return;
                }
            }


            if(makeGuess(guess[0], guess[1], enemyBoard, enemyShips, numShips, guessBoard))
            {
                shipDirection = guessDirection;
                guessDistance++;
            }
            else
            {//if it's a miss, rotate to the next direction
                switch(guessDirection)
                {
                    case 'u':
                        guessDirection = 'r';
                        break;
                    case 'r':
                        guessDirection = 'd';
                        break;
                    case 'd':
                        guessDirection = 'l';
                        break;
                    default://reset to random guessing (we've already guessed up at this point)
                        guessDirection = 'u';
                        shipDirection = '?';
                        lastHitCol = '?';
                        lastHitRow = 0;
                        break;
                }

                
            }


        }
        else
        {//know where a ship is, and know which direction we're guessing

            int guess[2] = {lastHitCol, lastHitRow};


            if(shipDirection == 'u'){
                guess[1] = lastHitRow - guessDistance;

                //if the guess is invalid,
                if(!isValidGuess(guess[0], guess[1], guessBoard)){
                    //start attacking the other side of the ship.
                    guessDistance = 1;
                    shipDirection = 'd';
                    guess[1] = lastHitRow + guessDistance;
                    //if this direction is also invalid (e.g already been guessed), we're done with this ship.
                    if(!isValidGuess(guess[0], guess[1], guessBoard)){
                        //so we need to start over and make a random move.
                        lastHitRow = 0;
                        lastHitCol = '?';
                        shipDirection = '?';
                        makeMove(enemyBoard, enemyShips, numShips, guessBoard);
                        return;
                    }
                }
            }
            else if(shipDirection == 'r')
            {
                guess[0] = lastHitCol + guessDistance;

                //if the guess is invalid,
                if(!isValidGuess(guess[0], guess[1], guessBoard)){
                    //start attacking the other side of the ship.
                    guessDistance = 1;
                    shipDirection = 'l';
                    guess[1] = lastHitCol - guessDistance;
                    //if this direction is also invalid (e.g already been guessed), we're done with this ship.
                    if(!isValidGuess(guess[0], guess[1], guessBoard)){
                        //so we need to start over and make a random move.
                        lastHitRow = 0;
                        lastHitCol = '?';
                        shipDirection = '?';
                        makeMove(enemyBoard, enemyShips, numShips, guessBoard);
                        return;
                    }
                }
            }
            else if(shipDirection == 'l')
            {
                guess[0] = lastHitCol - guessDistance;

                //if the guess is invalid,
                if(!isValidGuess(guess[0], guess[1], guessBoard)){
                    //start attacking the other side of the ship.
                    guessDistance = 1;
                    shipDirection = 'r';
                    guess[1] = lastHitCol + guessDistance;
                    //if this direction is also invalid (e.g already been guessed), we're done with this ship.
                    if(!isValidGuess(guess[0], guess[1], guessBoard)){
                        //so we need to start over and make a random move.
                        lastHitRow = 0;
                        lastHitCol = '?';
                        shipDirection = '?';
                        makeMove(enemyBoard, enemyShips, numShips, guessBoard);
                        return;
                    }
                }
            }
            else if(shipDirection == 'd'){
                guess[1] = lastHitRow + guessDistance;

                //if the guess is invalid,
                if(!isValidGuess(guess[0], guess[1], guessBoard)){
                    //start attacking the other side of the ship.
                    guessDistance = 1;
                    shipDirection = 'u';
                    guess[1] = lastHitRow - guessDistance;
                    //if this direction is also invalid (e.g already been guessed), we're done with this ship.
                    if(!isValidGuess(guess[0], guess[1], guessBoard)){
                        //so we need to start over and make a random move.
                        lastHitRow = 0;
                        lastHitCol = '?';
                        shipDirection = '?';
                        makeMove(enemyBoard, enemyShips, numShips, guessBoard);
                        return;
                    }
                }
            }


            if(makeGuess(guess[0], guess[1], enemyBoard, enemyShips, numShips, guessBoard))
            {
                guessDistance++;
            }
            else
            {//if it's a miss, flip to the other side.
                guessDistance = 1;
                switch(shipDirection){
                    case 'u':
                        shipDirection = 'd';
                        guess[1] = lastHitRow + 1;
                        break;
                    case 'r':
                        shipDirection = 'l';
                        guess[0] = lastHitCol - 1;
                        break;
                    case 'l':
                        shipDirection = 'r';
                        guess[0] = lastHitCol + 1;
                        break;
                    default:
                        shipDirection = 'u';
                        guess[1] = lastHitRow - 1;
                        break;
                }

                //if the guess is invalid, reset to random guessing
                if(!isValidGuess(guess[0], guess[1], guessBoard)){
                    guessDirection = 'u';
                    shipDirection = '?';
                    lastHitCol = '?';
                    lastHitRow = 0;
                }
            }
        }
    }
}

void MediumAI::placeShips(int numShips, Ship** shipList, Board* homeBoard){

}