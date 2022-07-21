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
  proto_config.serial_address_ = "/dev/ttySttyUSB012";
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
  proto_config.serial_address_ = "/dev/ttyUSB0";
  fishbot_config.protocol_config_ = proto_config;

  FishBotDriver fishbot_driver(fishbot_config);
  sleep(2);
}

TEST(TestFishBotDriver, TestSendSpeed) {
  using namespace fishbot::driver;  // NOLINT
  FishBotConfig fishbot_config;
  ProtocolConfig proto_config;
  proto_config.protocol_type_ = PROTOCOL_TYPE::SERIAL;
  proto_config.serial_baut_ = 115200;
  proto_config.serial_address_ = "/dev/ttyUSB0";
  fishbot_config.protocol_config_ = proto_config;

  FishBotDriver fishbot_driver(fishbot_config);
  // 设置电机0速度为0.05m/s
  fishbot_driver.GetMotor()->SendMotorSpeed(0, 0.05);
  fishbot_driver.GetMotor()->SendMotorSpeed(1, 0.06);
  sleep(1);
}
