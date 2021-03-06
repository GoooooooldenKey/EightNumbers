#include <string>
#include <string_view>
#include <iostream>
#include <vector>
#include "Board.h"
#include "BoardCmdRender.h"
using std::string;
using std::cout;
using std::endl;
using std::iterator;

struct BoardWithStep {
    Board board;
    std::string step;
};

typedef Board::Pos BPOS;
typedef std::vector<BoardWithStep> BoardCache;
typedef std::vector<BoardCache> Cache;

bool isRunning = true;
bool isFound = false;
size_t stepCount;

Board board = Board(3);
Board targetBoard = Board(3);
BoardCmdRender render = BoardCmdRender();
Cache cache;

void tick() {
    BoardCache boardcache;
    Board b(board.getSize());

    boardcache.shrink_to_fit();
    BoardCache::iterator it = (cache.end() - 1)->begin();

    stepCount++;
    for (; it != (cache.end() - 1)->end(); it++) {
        b = it->board;
        if (b.pullChessIntoBlank(Direction::up)) {
            boardcache.insert(boardcache.end(), BoardWithStep{ b, it->step + "U" });
            if (b == targetBoard) {
                isFound = true;
                break;
            }
        }
        b = it->board;
        if (b.pullChessIntoBlank(Direction::down)) {
            boardcache.insert(boardcache.end(), BoardWithStep{ b, it->step + "D" });
            if (b == targetBoard) {
                isFound = true;
                break;
            }
        }
        b = it->board;
        if (b.pullChessIntoBlank(Direction::left)) {
            boardcache.insert(boardcache.end(), BoardWithStep{ b, it->step + "L" });
            if (b == targetBoard) {
                isFound = true;
                break;
            }
        }
        b = it->board;
        if (b.pullChessIntoBlank(Direction::right)) {
            boardcache.insert(boardcache.end(), BoardWithStep{ b, it->step + "R" });
            if (b == targetBoard) {
                isFound = true;
                break;
            }
        }
    }
    it = boardcache.end() - 1;
    cache.insert(cache.end(), boardcache);


    if (isFound) {
        isRunning = false;
        cout << "From: \n" << render.Render(board) << endl << "To: \n" << render.Render(targetBoard) << endl;
        cout << "Steps:" << endl;

        Cache::iterator iterA = cache.begin();
        BoardCache::iterator iterB = iterA->begin();
        size_t l = 1;

        while (true) {
            if (it->step.substr(0, l) == iterB->step) {
                cout << iterB->step << endl << render.Render(iterB->board) << endl;
                if (it->step == iterB->step) break;
                iterA++;
                iterB = iterA->begin();
                l++;
            } else {
                iterB++;
            }
        }
        cout << stepCount << " steps in total.";
    }
}

void preInitialization() {
    board.putChess(BPOS(0, 0), Chess(2))
        .putChess(BPOS(0, 1), Chess())
        .putChess(BPOS(0, 2), Chess(3))
        .putChess(BPOS(1, 0), Chess(1))
        .putChess(BPOS(1, 1), Chess(8))
        .putChess(BPOS(1, 2), Chess(4))
        .putChess(BPOS(2, 0), Chess(7))
        .putChess(BPOS(2, 1), Chess(6))
        .putChess(BPOS(2, 2), Chess(5));

    targetBoard.putChess(BPOS(0, 0), Chess(1))
        .putChess(BPOS(0, 1), Chess(2))
        .putChess(BPOS(0, 2), Chess(3))
        .putChess(BPOS(1, 0), Chess(8))
        .putChess(BPOS(1, 1), Chess(0))
        .putChess(BPOS(1, 2), Chess(4))
        .putChess(BPOS(2, 0), Chess(7))
        .putChess(BPOS(2, 1), Chess(6))
        .putChess(BPOS(2, 2), Chess(5));

    cache.shrink_to_fit();
    stepCount = 0;
}

int main() {
    preInitialization();

    BoardCache boardcache;
    boardcache.insert(boardcache.end(), BoardWithStep{board, "S"});
    cache.insert(cache.end(), boardcache);
    
    while (isRunning) {
        tick();
    }
    return 0;
}