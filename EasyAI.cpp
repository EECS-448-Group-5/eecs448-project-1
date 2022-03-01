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
        col = rand() % 10;
        row = rand() % 10;
    }
    while(!guessBoard->isValidSpace(col, row));
    
    col = col + 97;
    char col_char = col;
    col = col - 97;

    for(int i=0; i<numShips; i++) {
        enemyShips[i]->hit(col_char, row);
    }

    if(!enemyBoard->isValidSpace(col, row)) {
        guessBoard->updateBoard(col_char, row, '*');
    }
    else {
        guessBoard->updateBoard(col_char, row, 'M');
    }
}