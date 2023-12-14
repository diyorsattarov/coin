#pragma once
#ifndef GAME_H
#define GAME_H

#include <coin/coin.h>

class Game {
public:
    Game(int rounds);
    void play();
    int getWinner() const;
    int getScore(int player) const;
private:
    int rounds;
    int score[2];
    Coin coin;

    void flipCoin();
};

#endif