#ifndef PLAYER_H
#define PLAYER_H

#include "Opponent.h"
#include <iostream>
#include <string>

class Player : public Opponent {
    public:
        Player();
        void makeMove(Board* enemyBoard, Ship** enemyShips, int numShips, Board* guessBoard);
        void placeShips(int numShips, Ship** shipList, Board* homeBoard);

    private:
        //bool makeGuess(char col, int row, Board* enemyBoard, Ship** enemyShips, int numShips, Board* guessBoard);

        //int lastHitRow;
        //char lastHitCol;
        //char shipDirection;
        //char guessDirection;
        //int guessDistance;
};

#endif