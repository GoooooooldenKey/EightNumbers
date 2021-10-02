#pragma once

class Chess {
private:
    size_t num;

public:
    size_t get() const;
    Chess& set(size_t);

    Chess(size_t numIn = 0);
};