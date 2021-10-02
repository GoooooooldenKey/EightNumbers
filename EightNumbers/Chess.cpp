#include "Chess.h"

size_t Chess::get() const{
    return this->num;
}

Chess& Chess::set(size_t numIn) {
    num = numIn;
    return *this;
}

Chess::Chess(size_t numIn) {
    this->num = numIn;
}
