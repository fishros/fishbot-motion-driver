/**
 * @brief 文件描述：测试ProtoDataFrame
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-17
 * @copyright 版权所有：FishBot Open Source Organization
 */

#include "fishbot/driver/app_protocol/data_frame.h"

#include "fishbot/driver/utils/proto_utils.h"
#include "gtest/gtest.h"

TEST(TestProtoDataFrame, TestDataParse) {
  using namespace fishbot::driver;  // NOLINT
  std::string data(
      "\x02"
      "\x01\x08\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x01\x08\x00\x01\x01\x02\x00\x00\x00\x00\x00\x00",
      26 - 1);
  std::vector<ProtoDataFrame> data_frames = ProtoDataFrame::ParseDataFrame(data);
  EXPECT_FLOAT_EQ(data_frames.size(), 0x02);
  EXPECT_FLOAT_EQ(data_frames[0].header_.data_id, 0x01);
  EXPECT_FLOAT_EQ(data_frames[0].header_.data_direction, 0x01);
  EXPECT_FLOAT_EQ(data_frames[0].header_.data_len, 0x08);

  proto_motor_encoder_data_t encoder =
      data_frames[0].GetData<proto_motor_encoder_data_t>();
  EXPECT_FLOAT_EQ(encoder.motor_encoder[0], 0x00);

  // EncoderDataFrame* ef = static_cast<EncoderDataFrame*>(&data_frames[0]);
  // EXPECT_FLOAT_EQ(ef->encoder_data_.motor_encoder[0], 0x00);
}

TEST(TestProtoDataFrame, TestStructHeader) {
  using namespace fishbot::driver;  // NOLINT
  proto_data_header_t header;
  std::memcpy(reinterpret_cast<uint8_t*>(&header), "\x01\x08\x00\x01", 4);
  EXPECT_FLOAT_EQ(header.data_id, 0x01);
  EXPECT_FLOAT_EQ(header.data_direction, 0x01);
  EXPECT_FLOAT_EQ(header.data_len, 0x08);

  EXPECT_FLOAT_EQ(sizeof(proto_data_header_t), 0x08);
}

TEST(TestProtoDataFrame, TestStructHeader2Str) {
  using namespace fishbot::driver;  // NOLINT
  proto_data_header_t header;
  header.data_direction = DATA_TO_MASTER;
  header.data_id = DATA_ENCODER;
  header.data_len = 0x04;
  print_frame_to_hex("test_header", reinterpret_cast<char*>(&header),
                     sizeof(header));
}

TEST(TestProtoDataFrame, TestStructEncoder) {
  using namespace fishbot::driver;  // NOLINT
  proto_motor_encoder_data_t data;
  std::memcpy(reinterpret_cast<uint8_t*>(&data), "\x01\x08\x00\x01", 4);

  EXPECT_FLOAT_EQ(sizeof(proto_data_header_t), 0x04);
}
