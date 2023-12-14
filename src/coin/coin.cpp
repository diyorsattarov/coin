#include <coin/coin.h>

Coin::Coin() : state(CoinState::Heads) { Utilities::console_logger()->info("Coin constructor called - Initial State: {}", Utilities::toString(state)); }

Coin::~Coin() { Utilities::console_logger()->info("Coin destructor called"); }

CoinState Coin::flipState() {
    //Utilities::console_logger()->info("Coin flip method called");
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    state = dis(gen) == 0 ? CoinState::Heads : CoinState::Tails;
    return state;
}

CoinState Coin::getState() {
    Utilities::console_logger()->info("Coin getState method called - Current State: {}", Utilities::toString(state));
    return state;
}