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
    
}