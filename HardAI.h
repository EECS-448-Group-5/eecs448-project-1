#ifndef HARDAI_H
#define HARDAI_H

#include "Opponent.h"
#include <string>

class HardAI : public Opponent {
    public: 
        HardAI();
        void makeMove(Board* enemyBoard, Ship** enemyShips, int numShips, Board* guessBoard);
        void makeRandomGuess(Board* enemyBoard, Ship** enemyShips, int numShips, Board* guessBoard);
    
    private: 
        void makeTargetedGuess(Board* enemyBoard, Ship** enemyShips, int numShips, Board* guessBoard);
};

#endif