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
  proto_config.serial_address_ = "/dev/ttyUSB0";
  fishbot_config.protocol_config_ = proto_config;

  FishBotDriver fishbot_driver(fishbot_config);


  //   EXPECT_FLOAT_EQ(sum_data > 0, true);
}
