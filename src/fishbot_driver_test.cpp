/**
 * @brief 文件描述：FishBotDriver测试
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-17
 * @copyright 版权所有：FishBot Open Source Organization
 */

#include "fishbot/driver/fishbot_driver.h"

#include "gtest/gtest.h"

TEST(TestFishBotDriver, TestReadFrame) {
  using namespace fishbot::driver;  // NOLINT
  FishBotConfig fishbot_config;
  ProtocolConfig proto_config;
  proto_config.protocol_type_ = PROTOCOL_TYPE::SERIAL;
  proto_config.serial_baut_ = 115200;
  proto_config.serial_address_ = "/dev/ttyS12";
  fishbot_config.protocol_config_ = proto_config;

  FishBotDriver fishbot_driver(fishbot_config);
  // fishbot_driver.UpdateData();
  sleep(3);
}

TEST(TestFishBotDriver, TestReadEncoder) {
  using namespace fishbot::driver;  // NOLINT
  FishBotConfig fishbot_config;
  ProtocolConfig proto_config;
  proto_config.protocol_type_ = PROTOCOL_TYPE::SERIAL;
  proto_config.serial_baut_ = 115200;
  proto_config.serial_address_ = "/dev/ttyS12";
  fishbot_config.protocol_config_ = proto_config;

  FishBotDriver fishbot_driver(fishbot_config);
  sleep(10);
  // EXPECT_EQ(fishbot_driver.recv_queue_.size() > 0, true);

  // while (fishbot_driver.recv_queue_.size() > 0) {
  //   ProtoFrame frame = fishbot_driver.recv_queue_.front();
  //   fishbot_driver.recv_queue_.pop();
  //   EXPECT_EQ(frame.frame_index_ > -1, true);
  //   EXPECT_EQ(frame.IsValidData(), true);
  //   EXPECT_EQ(frame.data_frame_len_ > 0, true);
  //   EXPECT_EQ(frame.data_frames_.size() > 0, true);

  
  // }
}
