#include <gtest/gtest.h>
#include <coin/coin.h>

class CoinTest : public ::testing::Test {
protected:
    Coin coin;
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(CoinTest, InitialStateTest) {
    ASSERT_EQ(coin.getState(), CoinState::Heads);
}

TEST_F(CoinTest, FlipConsistencyTest) {
    for (int i = 0; i < 100; ++i) {
        CoinState state = coin.flipState();
        ASSERT_TRUE(state == CoinState::Heads || state == CoinState::Tails);
    }
}

TEST_F(CoinTest, MultipleFlipsDistribution) {
    int totalHeads = 0;
    int totalTails = 0;
    const int numTrials = 10;
    const int numFlips = 1000;

    for (int j = 0; j < numTrials; ++j) {
        int heads = 0;
        int tails = 0;

        for (int i = 0; i < numFlips; ++i) {
            coin.flipState() == CoinState::Heads ? ++heads : ++tails;
        }

        totalHeads += heads;
        totalTails += tails;
    }

    float headsAverage = static_cast<float>(totalHeads) / numTrials;
    float tailsAverage = static_cast<float>(totalTails) / numTrials;

    Utilities::console_logger()->info("Average Heads: {}, Average Tails: {}", headsAverage, tailsAverage);
    ASSERT_NEAR(headsAverage, tailsAverage, numFlips * 0.1); // Allowing 10% deviation
}
