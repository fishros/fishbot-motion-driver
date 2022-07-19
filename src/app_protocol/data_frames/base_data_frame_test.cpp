/**
 * @brief 文件描述：测试BaseDataFrame
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-17
 * @copyright 版权所有：FishBot Open Source Organization
 */

#include "fishbot/driver/app_protocol/data_frames/base_data_frame.h"

#include "fishbot/driver/utils/proto_utils.h"
#include "gtest/gtest.h"

TEST(TestBaseDataFrame, TestDataParse) {
  using namespace fishbot::driver;  // NOLINT
  std::string data("\x01\x01\x04\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00",
                   13 - 1);
  BaseDataFrame data_frame = BaseDataFrame::ParseDataFrame(data);
  EXPECT_FLOAT_EQ(data_frame.header_.data_id, 0x01);
  EXPECT_FLOAT_EQ(data_frame.header_.data_direction, 0x01);
  EXPECT_FLOAT_EQ(data_frame.header_.data_len, 0x04);

  EXPECT_FLOAT_EQ(
      static_cast<EncoderDataFrame>(data_frame).encoder_data_.motor_encoder[0],
      0x00);
}

TEST(TestBaseDataFrame, TestStructHeader) {
  using namespace fishbot::driver;  // NOLINT
  proto_data_header_t header;
  std::memcpy(reinterpret_cast<uint8_t*>(&header), "\x01\x04\x00\x01", 4);
  EXPECT_FLOAT_EQ(header.data_id, 0x01);
  EXPECT_FLOAT_EQ(header.data_direction, 0x01);
  EXPECT_FLOAT_EQ(header.data_len, 0x04);

  EXPECT_FLOAT_EQ(sizeof(proto_data_header_t), 0x04);
}

TEST(TestBaseDataFrame, TestStructHeader2Str) {
  using namespace fishbot::driver;  // NOLINT
  proto_data_header_t header;
  header.data_direction = DATA_TO_MASTER;
  header.data_id = DATA_ENCODER;
  header.data_len = 0x04;
  print_frame_to_hex("test_header", reinterpret_cast<char*>(&header),
                     sizeof(header));
}
