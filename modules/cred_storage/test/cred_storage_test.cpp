/**
 * @file
 * @brief Test implementation
 * @defgroup cred_storage_test
 * @{
 */

#include <string.h>
#include <stdlib.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "fs_mock.hpp"
extern "C" {
#include "cred_storage.c"
}

std::unique_ptr<FsMock> fsMockPtr;

class CredStorageTest : public ::testing::Test
{
  struct Parameters
  {
    credentials_t credentials{};
  };

protected:
  
  static constexpr const char *USERNAME = "Admin";
  static constexpr const char *PASSWORD = "very_strong_password";

  void SetUp()
  {
    strcpy(parameters.credentials.username, USERNAME);
    strcpy(parameters.credentials.password, PASSWORD);
    fsMockPtr.reset(new FsMock);
  }

  void TearDown()
  {
    fsMockPtr.reset();
  }

  Parameters parameters;
};

TEST_F(CredStorageTest, storeTest)
{
  char* expectedFileData = "Admin\r\nvery_strong_password";
  EXPECT_CALL(*fsMockPtr, fs_write_string(::testing::StrEq(CREDENTIALS_FILENAME), ::testing::StrEq(expectedFileData)))
    .Times(1)
    .WillOnce(::testing::Return(FS_RET_OK));

  cred_storage_ret_values res = cred_storage_save_credentials(&parameters.credentials);
  EXPECT_EQ(CRED_ST_RET_OK, res);
  EXPECT_TRUE(0 == std::memcmp(&g_credentials, &parameters.credentials, sizeof(credentials_t)));
}

TEST_F(CredStorageTest, storeFsFailTest)
{
  char* expectedFileData = "Admin\r\nvery_strong_password";
  EXPECT_CALL(*fsMockPtr, fs_write_string(::testing::StrEq(CREDENTIALS_FILENAME), ::testing::StrEq(expectedFileData)))
    .Times(1)
    .WillOnce(::testing::Return(FS_RET_ERR));

  cred_storage_ret_values res = cred_storage_save_credentials(&parameters.credentials);
  EXPECT_EQ(CRED_ST_RET_ERR, res);
  EXPECT_EQ(strlen(g_credentials.username), 0);
  EXPECT_EQ(strlen(g_credentials.password), 0);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

/** @} */