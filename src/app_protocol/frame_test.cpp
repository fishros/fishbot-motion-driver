/**
 * @brief 文件描述：测试ProtoFrame
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-17
 * @copyright 版权所有：FishBot Open Source Organization
 */

#include "fishbot/driver/app_protocol/frame.h"

#include "gtest/gtest.h"

TEST(TestProtoFrame, TestDataParse) {
  using namespace fishbot::driver;  // NOLINT
  std::string data(
      "\x5A\xEA\x01\x01\x04\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\xB9\x11"
      "\x5A",
      19 - 1);
  ProtoFrame base_frame(data);

  EXPECT_FLOAT_EQ(base_frame.target_addr_,0x01);
  EXPECT_FLOAT_EQ(base_frame.frame_index_,0xEA);
  EXPECT_TRUE(base_frame.IsValidData());
  EXPECT_EQ(base_frame.data_frame_len_, 1);
}

//
TEST(TestProtoFrame, TestCRC16) {
  using namespace fishbot::driver;  // NOLINT
  std::string data("\x01\x03\x04\x00\x02\x5A\x00\x00\x00", 10 - 1);
  uint16_t result = crc16((uint8_t*)data.data(), data.size());
  std::cout<<result<<std::endl;
}