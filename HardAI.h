/**------------------------------------------------------------------------
 * @file : HardAI.h
 * @author : Mickey McMahon
 * @assignment : EECS448 - Project 2
 * @brief : Header file that defines all variables and methods for HardAI class
 * @date: 03-06-22
 *
 ------------------------------------------------------------------------ **/

#ifndef HARDAI_H
#define HARDAI_H

#include "Opponent.h"
#include <string>

class HardAI : public Opponent {
    public: 

        /**
       * @pre : None
       * @post :  None
       * @param :  None
       * @throw : None
       * @return : None
        **/
        HardAI();

        /**
       * @pre : None
       * @post :  Calls makeTargetedGuess
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
        /**
       * @pre : None
       * @post :  Scans an enemy's board and looks for the first available target
       * @param : Board* enemyBoard, Ship** enemyShips, int numShips, Board* guessBoard
       * @throw : None
       * @return : None
        **/
        void makeTargetedGuess(Board* enemyBoard, Ship** enemyShips, int numShips, Board* guessBoard);
        int hitCount;
};

#endif