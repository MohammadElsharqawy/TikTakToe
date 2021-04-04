#include "Move.h"

#ifndef TIKTAKTOE_TIKTAKTOE_H
#define TIKTAKTOE_TIKTAKTOE_H


class TikTakToe {
private:
    char player, computer, grid[3][3]{};

    void print() ;
    void playerMove() ;
    void computerMove() ;
    Move minimax(bool maximizingPlayer) ;
    bool win();
    bool tie();
public:

    TikTakToe() ;
    void play() ;
};


#endif //TIKTAKTOE_TIKTAKTOE_H
