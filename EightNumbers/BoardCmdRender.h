#pragma once

//这里的code style和其他地方不一样, 主要是为了尝试一些新接触的特性.

#include "Board.h"
#include <string>

#define EACH(X, N) size_t N = 0; N < X; ++N

using std::string;

class BoardCmdRender {
public:
    string Render(Board& board) {
        string out;
        for (EACH(board.getSize(), x)) { //row
            for (EACH(board.getSize(), y)) { //col
                size_t n = board.getChess(Board::Pos(x, y)).get();
                out += "\t";
                out += n == 0 ? " " : std::to_string(n);
                out += "\t";
            }
            out += "\n\n";
        }
        return out;
    }
};

#undef EACH