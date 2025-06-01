#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Account.h"

using ::testing::Return;
using ::testing::_;

class MockDatabase {
public:
    MOCK_METHOD(bool, saveToDatabase, (Account& account, int sum), (override));
};

TEST(AccountTest, ChangeBalanceSuccess) {
    Account account(1, 100);
    account.lock();
    account.changeBalance(50);
    account.unlock();
    EXPECT_EQ(account.getBalance(), 150);
}

TEST(AccountTest, ChangeBalanceLocked) {
    Account account(1, 100);
    account.lock();
    EXPECT_THROW(account.changeBalance(50), std::runtime_error);
    account.unlock();
}

TEST(AccountTest, SaveToDatabase) {
    MockDatabase mockDb;
    Account account(1, 100);
    EXPECT_CALL(mockDb, saveToDatabase(_, _)).WillOnce(Return(true));
    account.lock();
    account.changeBalance(50);
    account.unlock();
    // Проверяем, что saveToDatabase был вызван (если это часть логики)
}