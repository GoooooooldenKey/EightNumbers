#pragma once

//�����code style�������ط���һ��, ��Ҫ��Ϊ�˳���һЩ�½Ӵ�������.

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