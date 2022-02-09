/**
 * @file
 * @brief Implement FS mocks
 * @addtogroup cred_storage_test
 * @{
 */

#include <memory>
#include "fs_mock.hpp"

extern std::unique_ptr<FsMock> fsMockPtr;

fs_ret_values fs_write_string(const char* path, const char* data)
{
  return fsMockPtr->fs_write_string(path, data);
}

int fs_read(const char* path, char* data, unsigned short data_size)
{
  return fsMockPtr->fs_read(path, data, data_size);
}

/** @} */