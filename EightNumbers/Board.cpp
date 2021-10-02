#include "Board.h"

size_t Board::posToIndex(const Pos posIn) {
    return (posIn.X * this->size) + posIn.Y;
}

Chess& Board::getChess(const Pos posIn) {
    return board.at(posToIndex(posIn));
}

Board::Pos Board::findFirstBlank() {
    //loop the rows
    for (size_t x = 0; x < this->size; ++x) {
        //loop the columns
        for (size_t y = 0; y < this->size; ++y) {
            if (getChess(Pos(x, y)).get() == 0) {
                return Pos(x, y);
            }
        }
    }
}

void Board::updateBlank() {
    blank = findFirstBlank();
}

Board& Board::moveChess(Pos fromPos, Pos toPos) {
    Chess tempChess;
    tempChess = this->getChess(toPos);
    this->getChess(toPos) = this->getChess(fromPos);
    this->getChess(fromPos) = tempChess;
    updateBlank();
    return *this;
}

Board::Board(size_t sizeIn) {
    board.reserve(sizeIn * sizeIn);

    //store size
    this->size = sizeIn;

    //put all zero chess
    for (size_t i = 0; i < sizeIn * sizeIn; ++i) {
        board.insert(board.end(), Chess());
    }

    //store the first blank
    updateBlank();
}

bool Board::operator==(const Board& boardRight) const {

    if (this->size != boardRight.size) {
        return false;
    }

    for (size_t i = 0; i < this->size * this->size; ++i) {
        if (this->board.at(i).get() != boardRight.board.at(i).get()) {
            return false;
        }
    }

    return true;
}


bool Board::pullChessIntoBlank(Direction directionFrom) {
    switch (directionFrom) {

    case Direction::up:
        if (blank.X > 0) {
            moveChess(Pos(blank.X - 1, blank.Y), blank);
            return true;
        }
        break;

    case Direction::down:
        if (blank.X < size - 1) {
            moveChess(Pos(blank.X + 1, blank.Y), blank);
            return true;
        }
        break;

    case Direction::left:
        if (blank.Y > 0) {
            moveChess(Pos(blank.X, blank.Y - 1), blank);
            return true;
        }
        break;

    case Direction::right:
        if (blank.Y < size - 1) {
            moveChess(Pos(blank.X, blank.Y + 1), blank);
            return true;
        }
        break;
    }
    return false;
}

Board& Board::putChess(Pos posIn, Chess chessIn) {
    this->getChess(posIn) = chessIn;
    updateBlank();
    return *this;
}

size_t Board::getSize() const {
    return this->size;
}

Board::Pos::Pos(size_t x, size_t y) {
    this->X = x;
    this->Y = y;
}

Board::Pos::Pos() {
    this->X = 0;
    this->Y = 0;
}
