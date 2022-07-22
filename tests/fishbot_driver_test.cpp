/**
 * @brief 文件描述：FishBotDriver测试
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-17
 * @copyright 版权所有：FishBot Open Source Organization
 */

#include "fishbot/driver/fishbot_driver.h"

#include "gtest/gtest.h"

TEST(TestFishBotDriver, TestReadUdpFrame) {
  using namespace fishbot::driver;  // NOLINT
  FishBotConfig fishbot_config;
  ProtocolConfig proto_config;
  proto_config.protocol_type_ = PROTOCOL_TYPE::UDP_SERVER;
  proto_config.udp_server_ip_ = "0.0.0.0";
  proto_config.udp_server_port_ = 3474;
  fishbot_config.protocol_config_ = proto_config;
  FishBotDriver fishbot_driver(fishbot_config);
  // fishbot_driver.UpdateData();
  sleep(10);
}

TEST(TestFishBotDriver, TestReadSerialFrame) {
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

TEST(TestFishBotDriver, TestReadSerialEncoder) {
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

  for (int i = 0; i < 0.3 * 100; i++) {
    fishbot_driver.GetMotor()->SendMotorSpeed(0, static_cast<float>(i) / 100);
    fishbot_driver.GetMotor()->SendMotorSpeed(1, 0.001);
    sleep(1);
  }
  fishbot_driver.GetMotor()->SendMotorSpeed(0, 0.00);
  sleep(1);
}

TEST(TestFishBotDriver, TestSendSpeedByUDP) {
  using namespace fishbot::driver;  // NOLINT
  FishBotConfig fishbot_config;
  ProtocolConfig proto_config;
  proto_config.protocol_type_ = PROTOCOL_TYPE::UDP_SERVER;
  proto_config.udp_server_ip_ = "0.0.0.0";
  proto_config.udp_server_port_ = 3474;
  fishbot_config.protocol_config_ = proto_config;
  FishBotDriver fishbot_driver(fishbot_config);

  for (int i = 0; i < 0.3 * 100; i++) {
    fishbot_driver.GetMotor()->SendMotorSpeed(0, static_cast<float>(i) / 100);
    fishbot_driver.GetMotor()->SendMotorSpeed(1, -static_cast<float>(i) / 100);
    sleep(1);
  }
  fishbot_driver.GetMotor()->SendMotorSpeed(0, 0.00);
  fishbot_driver.GetMotor()->SendMotorSpeed(1, 0.00);
  sleep(1);
}
