#pragma once
#include <vector>
#include "Chess.h"

enum class Direction { 
    up,
    down,
    left,
    right
};

class Board {
public: class Pos {
    public:
        size_t X;
        size_t Y;

        Pos(size_t x, size_t y);
        Pos();
    };

private:
    std::vector<Chess> board; //an array that stored all the chesses
    size_t size; //the number of both rows&cols
    Pos blank;

    size_t posToIndex(const Pos posIn); //return the index of the specific pos on board
    Pos findFirstBlank();
    void updateBlank();
    Board& moveChess(Pos fromPos, Pos toPos); //actually exchange 2 chesses at the given coordinates

public:
    bool pullChessIntoBlank(Direction directionFrom);//pull the chess from the specific direction into the blank position. return true if success, otherwise false.
    Chess& getChess(const Pos posIn); //get chess instance at the given coordinate
    Board& putChess(Pos posIn, Chess chessIn); //put&replace a chess at a specific pos. return self instance
    size_t getSize() const;

    Board(size_t sizeIn = 1); //generate a size*size(1*1 by default) martix, and put all zero(No Chess on it)

    bool operator==(const Board& boardRight) const;
};