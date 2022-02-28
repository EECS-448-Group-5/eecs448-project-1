#ifndef MEDAI_H
#define MEDAI_H

#include "Opponent.h"
#include <string>

class MediumAI : public Opponent {
    public:
        void makeMove(Board* enemyBoard);
        void placeShips(int numShips, Board* homeBoard);

    private:
        std::string lastHit;
        char shipDirection;
};

#endif