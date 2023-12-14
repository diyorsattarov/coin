#pragma once
#ifndef COIN_H
#define COIN_H

enum class CoinState {
    Heads,
    Tails
};

class Coin {
public:
    Coin();
    ~Coin();
    CoinState flip();
private:
    CoinState state;
};

#endif