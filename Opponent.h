#ifndef OPPONENT_H
#define OPPONENT_H

#include <stdlib.h> //srand, rand
#include "board.h"

class Opponent {
    public:

    virtual void makeMove(Board* enemyBoard, Ship** enemyShips, int numShips, Board* guessBoard) = 0;
    
    virtual void placeShips(int numShips, Ship** shipList, Board* homeBoard){
        for(int i=numShips; i>0; i--){
            Ship* nextShip = nullptr;
            bool invalid = true;
            while(invalid){
                invalid = false;
                int base[2] = {97, 0};//getRandomGuess();

                //random direction
                int isVert = rand() % 2;

                //ensure each space of the ship is valid.
                for(int j=0; j<i; j++){
                    //check if the j-th tile of the ship would be invalid
                    if(!isValidGuess(base[0] + j*isVert, base[1] + j*(1-isVert), homeBoard)){
                        invalid = true;
                        break;
                    }
                }

                //at this point, we have a valid ship location, so we go ahead and create the ship
                if(isVert){
                    nextShip = new Ship(i, 'v', base[0], base[1]);
                }else{
                    nextShip = new Ship(i, 'h', base[0], base[1]);
                }
            }

            shipList[i-1] = nextShip;
            homeBoard->placeShip(nextShip);
        }
    };

    protected:

    bool isValidGuess(char col, int row, Board* guessBoard){
        return col >= 97 && col <= 106 && 
           row >= 1 && row <= 10 && 
           guessBoard->isValidSpace(col - 97, row);
    }
};

#endif