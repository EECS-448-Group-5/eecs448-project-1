/**------------------------------------------------------------------------
 * @file : EasyAI.h
 * @author : Mickey McMahon
 * @assignment : EECS448 - Project 2
 * @brief : Header file that defines all variables and methods for EasyAI class
 * @date: 03-06-22
 *
 ------------------------------------------------------------------------ **/
#ifndef EASYAI_H
#define EASYAI_H

#include "Opponent.h"
#include <string>

class EasyAI : public Opponent {
    public: 
        /**
       * @pre : None
       * @post :  None
       * @param :  None
       * @throw : None
       * @return : None
        **/
        EasyAI();

        /**
       * @pre : None
       * @post :  Calls makeRandomGuess
       * @param : Board* enemyBoard, Ship** enemyShips, int numShips, Board* guessBoard
       * @throw : None
       * @return : None
        **/
        void makeMove(Board* enemyBoard, Ship** enemyShips, int numShips, Board* guessBoard);

        /**
       * @pre : None
       * @post :  Creates a random coordinate to hit then updates the guess and opponent's board 
       * @param : Board* enemyBoard, Ship** enemyShips, int numShips, Board* guessBoard
       * @throw : None
       * @return : None
        **/
        void makeRandomGuess(Board* enemyBoard, Ship** enemyShips, int numShips, Board* guessBoard);
    
    private: 
        
};

#endif