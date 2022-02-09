/**
 * @file
 * @brief Declare fs mocks
 * @addtogroup cred_storage_test
 * @{
 */

#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "fs.h"

class FsMockIface
{
public:
  virtual ~FsMockIface() {}

  virtual fs_ret_values fs_write_string(const char* path, const char* data) = 0;
  virtual int fs_read(const char* path, char* data, unsigned short data_size) = 0;
};

class FsMock : public FsMockIface
{
public:
  ~FsMock() override {}
  MOCK_METHOD(fs_ret_values, fs_write_string, (const char*, const char*), (override));

  MOCK_METHOD(int, fs_read, (const char*, char*, unsigned short), (override));
};

/** @} */