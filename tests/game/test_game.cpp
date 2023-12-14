#include <gtest/gtest.h>
#include <game/game.h>

class GameTest : public ::testing::Test {
protected:
    Game *game;
    const int rounds = 1000;

    void SetUp() override {
        game = new Game(rounds);
    }

    void TearDown() override {
        delete game;
    }
};

TEST_F(GameTest, PlayGame) {
    game->play();
    int winner = game->getWinner();

    // Winner should be -1 (tie), 0, or 1
    ASSERT_TRUE(winner >= -1 && winner <= 1);
}

TEST_F(GameTest, CorrectNumberOfRounds) {
    game->play();
    int winner = game->getWinner();
    int totalScore = game->getScore(0) + game->getScore(1);

    // Total score should equal number of rounds
    ASSERT_EQ(totalScore, rounds);
}

TEST_F(GameTest, NoWinnerInTie) {
    Game tieGame(2); // A game with only 2 rounds to increase chance of a tie
    tieGame.play();
    int winner = tieGame.getWinner();

    // In case of a tie, winner should be -1
    if (tieGame.getScore(0) == tieGame.getScore(1)) {
        ASSERT_EQ(winner, -1);
    }
}

TEST_F(GameTest, CorrectWinner) {
    game->play();
    int winner = game->getWinner();

    // Ensure the winner's score is higher than the loser's, unless it's a tie
    if (winner != -1) {
        ASSERT_GT(game->getScore(winner), game->getScore(1 - winner));
    }
}
