#ifndef OPPONENT_H
#define OPPONENT_H

#include "board.h"

class Opponent {
    public:

    virtual void makeMove(Board* enemyBoard, Ship** enemyShips, int numShips, Board* guessBoard) = 0;
    virtual void placeShips(int numShips, Ship** shipList, Board* homeBoard) = 0;
};

#endif