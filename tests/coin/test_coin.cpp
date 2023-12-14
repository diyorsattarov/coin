#include <gtest/gtest.h>
#include <coin/coin.h>

class CoinTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(CoinTest, FirstCoinTest) {
    ASSERT_EQ(1, 1);
}