#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Transaction.h"

using ::testing::Return;
using ::testing::_;

class MockAccount {
public:
    MOCK_METHOD(void, changeBalance, (int diff), (override));
    MOCK_METHOD(int, getBalance, (), (const, override));
    MOCK_METHOD(void, lock, (), (override));
    MOCK_METHOD(void, unlock, (), (override));
};

TEST(TransactionTest, CreditSuccess) {
    MockAccount mockAccount;
    EXPECT_CALL(mockAccount, getBalance()).WillOnce(Return(100));
    EXPECT_CALL(mockAccount, lock());
    EXPECT_CALL(mockAccount, changeBalance(50));
    EXPECT_CALL(mockAccount, unlock());
    Transaction::credit(mockAccount, 50);
}

TEST(TransactionTest, DebitSuccess) {
    MockAccount mockAccount;
    EXPECT_CALL(mockAccount, getBalance()).WillOnce(Return(150));
    EXPECT_CALL(mockAccount, lock());
    EXPECT_CALL(mockAccount, changeBalance(-50));
    EXPECT_CALL(mockAccount, unlock());
    EXPECT_TRUE(Transaction::debit(mockAccount, 50));
}

TEST(TransactionTest, DebitInsufficientFunds) {
    MockAccount mockAccount;
    EXPECT_CALL(mockAccount, getBalance()).WillOnce(Return(20));
    EXPECT_CALL(mockAccount, lock());
    EXPECT_CALL(mockAccount, unlock());
    EXPECT_FALSE(Transaction::debit(mockAccount, 50));
}