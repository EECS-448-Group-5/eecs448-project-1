#include "HardAI.h"
#include "board.h"
#include "ship.h"
#include <string>
#include <math.h>
#include <cstdlib>
#include <time.h>

HardAI::HardAI() {
    
}

void HardAI::makeMove(Board* enemyBoard, Ship** enemyShips, int numShips, Board* guessBoard) {
    makeTargetedGuess(enemyBoard, enemyShips, numShips, guessBoard);
}

void HardAI::makeRandomGuess(Board* enemyBoard, Ship** enemyShips, int numShips, Board* guessBoard) {
    
}

void HardAI::makeTargetedGuess(Board* enemyBoard, Ship** enemyShips, int numShips, Board* guessBoard) {
    int col = 0;
    int row = 0;
    do {
        for(int i=0; i<10; i++) {
            for (int j=0; j<10; j++) {
                if(!enemyBoard->isValidSpace(col, row) && guessBoard->isValidSpace(col, row)) {
                    row = i;
                    col = j;
                }
            }
        }
    }
    while(enemyBoard->isValidSpace(col, row));
    
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
