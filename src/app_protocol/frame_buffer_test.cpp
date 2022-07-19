/**
 * @brief 文件描述：测试FrameBuffer
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-17
 * @copyright 版权所有：FishBot Open Source Organization
 */

#include "fishbot/driver/app_protocol/frame_buffer.h"

#include "gtest/gtest.h"

TEST(TestFrame, TestFrameSplit) {
  using namespace fishbot::driver;  // NOLINT
  FrameBuffer buffer;
  std::string raw_data(
      "\x5A\x01\x02\x51\x02\x50\x01\x5A"
      "\x5A\x02\x02\x51\x02\x50\x0A\x5A"
      "\x5A\x03\x02\x50\x0A\x50\x05\x5A"
      "\x5A\x04\x02\x51\x02\x50\x05\x5A",
      32);
  buffer.PushRawData(raw_data.substr(0, 13));
  buffer.PushRawData(raw_data.substr(13, 3));
  buffer.PushRawData(raw_data.substr(16, 33 - 16));
  BaseFrame frame;
  for (int i = 0; i < 4; i++) {
    buffer.GetFrame(frame);
    // print_frame_to_hex("raw_data", frame.raw_data_.data(),
    //                    frame.raw_data_.size());
    EXPECT_FLOAT_EQ(frame.raw_data_.size() > 0, 1);
  }
}
