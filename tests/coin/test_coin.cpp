#include <gtest/gtest.h>
#include <coin/coin.h>

class CoinTest : public ::testing::Test {
protected:
    Coin coin;
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(CoinTest, FirstCoinTest) {
    ASSERT_EQ(coin.getState(), CoinState::Heads);
}

TEST_F(CoinTest, MultipleFlipsDistribution) {
    float headsAverage = 0;
    float tailsAverage = 0;
    for (int j = 0; j < 10; ++j) {
        int heads = 0;
        int tails = 0;
        const int numFlips = 1000;

        for (int i = 0; i < numFlips; ++i) {
            if (coin.flipState() == CoinState::Heads) {
                ++heads;
            } else {
                ++tails;
            }
        }
        Utilities::console_logger()->info("Heads: {} Tails: {}", heads, tails);
        ASSERT_NEAR(heads, tails, numFlips * 0.1); // Allowing 10% deviation
        headsAverage += heads;
        tailsAverage += tails;
    }
    Utilities::console_logger()->info("headsAverage: {} tailsAverage: {}", headsAverage/100, tailsAverage/100);
}