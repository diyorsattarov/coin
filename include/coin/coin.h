#pragma once
#ifndef COIN_H
#define COIN_H

class Coin {
public:
    Coin();
    ~Coin();
    bool getCoin();
private:
    bool coin;
};

#endif