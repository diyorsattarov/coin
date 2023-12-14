#pragma once
#ifndef COIN_H
#define COIN_H

#include <utilities/utilities.h>

enum class CoinState {
    Heads,
    Tails
};

class Coin {
public:
    Coin();
    ~Coin();
    CoinState flip();
    CoinState getState();
private:
    CoinState state;
};

#endif