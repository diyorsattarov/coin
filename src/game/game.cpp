#include <game/game.h>
#include <utilities/utilities.h>  // Make sure to include the header for Utilities

Game::Game(int rounds) : rounds(rounds) {
    score[0] = 0;
    score[1] = 0;
    Utilities::console_logger()->info("Game constructor called - Rounds: {}", rounds);
}

void Game::play() {
    Utilities::console_logger()->info("Starting game play - Total Rounds: {}", rounds);
    for (int i = 0; i < rounds; ++i) {
        flipCoin();
    }
    Utilities::console_logger()->info("Game play ended");
}

void Game::flipCoin() {
    CoinState result = coin.flipState();
    //Utilities::console_logger()->info("Coin flipped - Result: {}", Utilities::toString(result));

    if (result == CoinState::Heads) {
        ++score[0];
        //Utilities::console_logger()->info("Incremented score for Player 0 - New Score: {}", score[0]);
    } else {
        ++score[1];
        //Utilities::console_logger()->info("Incremented score for Player 1 - New Score: {}", score[1]);
    }
}

int Game::getWinner() const {
    int winner = -1; // Default for a tie
    if (score[0] > score[1]) winner = 0;
    if (score[1] > score[0]) winner = 1;

    Utilities::console_logger()->info("Game getWinner called - Winner: {}", winner == -1 ? "Tie" : std::to_string(winner));
    return winner;
}

int Game::getScore(int player) const {
    Utilities::console_logger()->info("Game getScore called - Player: {}, Score: {}", player, score[player]);
    return score[player];
}
