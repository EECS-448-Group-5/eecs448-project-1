#ifndef OPPONENT_H
#define OPPONENT_H

#include <stdlib.h> //srand, rand
#include <iostream>
#include <cstdlib>
#include <time.h>
#include "board.h"

class Opponent {
    public:

    virtual void makeMove(Board* enemyBoard, Ship** enemyShips, int numShips, Board* guessBoard) = 0;
    
    virtual void placeShips(int numShips, Ship** shipList, Board* homeBoard){
        //std::cout << "I AM HERE\n";
        int* base;
        for(int i=numShips; i>0; i--){
            Ship* nextShip = nullptr;
            bool invalid = true;
            while(invalid){
                invalid = false;
                base = getRandomGuess(homeBoard);

                std::cout << base[0] << ", " << base[1] << '\n';

                //random direction
                int isVert = rand() % 2;

                //ensure each space of the ship is valid.
                for(int j=0; j<i; j++){
                    //check if the j-th tile of the ship would be invalid
                    std::cout << "tile: "<< (char)(base[0] + j*isVert) << ", " << base[1] + j*(1-isVert) <<"\n";
                    if(!isValidGuess(base[0] + j*isVert, base[1] + j*(1-isVert), homeBoard)){
                        invalid = true;
                        break;
                    }
                }

                if(invalid) continue;

                //at this point, we have a valid ship location, so we go ahead and create the ship
                std::cout << "len "<<i<<", dir "<<isVert <<", coords "<<base[0]<<" "<<base[1]<<"\n";
                if(isVert){
                    nextShip = new Ship(i, 'v', base[0], base[1]);
                }else{
                    nextShip = new Ship(i, 'h', base[0], base[1]);
                }
            }

            shipList[i-1] = nextShip;
            homeBoard->placeShip(nextShip);
        }

        delete[] base;
    };

    virtual void makeRandomGuess(Board* enemyBoard, Ship** enemyShips, int numShips, Board* guessBoard) {
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

    protected:

    bool isValidGuess(char col, int row, Board* guessBoard){
        return col >= 97 && col <= 106 && 
           row >= 1 && row <= 10 && 
           guessBoard->isValidSpace(col - 97, row);
    }

    int* getRandomGuess(Board* guessBoard){
        //srand(time(NULL));
        int col = 0;
        int row = 0;
        do {
            col = rand() % 10;
            row = rand() % 10;
        }
        while(!guessBoard->isValidSpace(col, row));
    
        col = col + 97;
        char col_char = col;

        int* guess = new int[2];//{col_char, row};
        guess[0] = col_char;
        guess[1] = row + 1;

        std::cout << col_char << ", " << row+1 << '\n';

        return guess;
    }
};

#endif