/**------------------------------------------------------------------------
 * @file : HardAI.cpp
 * @author : Mickey McMahon
 * @assignment : EECS448 - Project 2
 * @brief : Implements all variables and methods for HardAI class
 * @date: 03-06-22
 *
 ------------------------------------------------------------------------ **/

#include "HardAI.h"
#include "board.h"
#include "ship.h"
#include <string>
#include <math.h>
#include <cstdlib>
#include <time.h>

HardAI::HardAI() {
    hitCount = 0;
}

void HardAI::makeMove(Board* enemyBoard, Ship** enemyShips, int numShips, Board* guessBoard) {
    makeTargetedGuess(enemyBoard, enemyShips, numShips, guessBoard);
}

void HardAI::makeRandomGuess(Board* enemyBoard, Ship** enemyShips, int numShips, Board* guessBoard) {
    
}

void HardAI::makeTargetedGuess(Board* enemyBoard, Ship** enemyShips, int numShips, Board* guessBoard) {
    int col = 0;
    int row = 0;
    
    //to make a targeted guess we scan the opponent's board for the first available target
    for(int i=0; i<10; i++) { 
        for (int j=0; j<10; j++) {
            if(!enemyBoard->isValidSpace(j, i) && guessBoard->isValidSpace(j, i)) { //only set the coordinates to target if the enemy has a ship there and the AI hasn't guessed there before
                row = i;
                col = j;
            }
        }
    }
    
    col = col + 97;
    char col_char = col;
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
