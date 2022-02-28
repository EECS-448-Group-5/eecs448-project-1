#ifndef OPPONENT_H
#define OPPONENT_H

#include "board.h"

class Opponent {
    public:

    virtual void makeMove(Board* enemyBoard) = 0;
    virtual void placeShips(int numShips, Board* homeBoard) = 0;
};

#endif