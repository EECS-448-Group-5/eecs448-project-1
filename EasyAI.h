#ifndef EASYAI_H
#define EASYAI_H

#include "Opponent.h"
#include <string>

class EasyAI : public Opponent {
    public: 
        EasyAI();
        void makeMove(Board* enemyBoard, Ship** enemyShips, int numShips, Board* guessBoard);
        void makeRandomGuess(Board* enemyBoard, Ship** enemyShips, int numShips, Board* guessBoard);
    
    private: 
        
};

#endif