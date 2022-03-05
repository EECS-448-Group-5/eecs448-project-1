#include "EasyAI.h"
#include "board.h"
#include "ship.h"
#include <string>
#include <math.h>
#include <cstdlib>
#include <time.h>

EasyAI::EasyAI() {

}

void EasyAI::makeMove(Board* enemyBoard, Ship** enemyShips, int numShips, Board* guessBoard) {
    makeRandomGuess(enemyBoard, enemyShips, numShips, guessBoard);
}

void EasyAI::makeRandomGuess(Board* enemyBoard, Ship** enemyShips, int numShips, Board* guessBoard) {
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