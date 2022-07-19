/**
 * @brief 文件描述：测试BaseFrame
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-17
 * @copyright 版权所有：FishBot Open Source Organization
 */

#include "fishbot/driver/app_protocol/base_frame.h"

#include "gtest/gtest.h"

TEST(TestBaseFrame, TestDataParse) {
  using namespace fishbot::driver;  // NOLINT
  std::string data(
      "\x5A\xEA\x01\x01\x04\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\xB9\x11"
      "\x5A",
      19 - 1);
  BaseFrame base_frame(data);

  EXPECT_FLOAT_EQ(base_frame.target_addr_, 0x01);
  EXPECT_FLOAT_EQ(base_frame.frame_index_, 0xEA);
  EXPECT_FLOAT_EQ(base_frame.IsValidData(), true);
  EXPECT_FLOAT_EQ(base_frame.data_frame_len_, 1);
}

