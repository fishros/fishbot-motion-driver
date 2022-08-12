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
  using namespace fishbot::driver; // NOLINT
  using namespace fish_protocol;   // NOLINT
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
  using namespace fishbot::driver; // NOLINT
  using namespace fish_protocol;   // NOLINT
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
  using namespace fishbot::driver; // NOLINT
  using namespace fish_protocol;   // NOLINT
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
  using namespace fishbot::driver; // NOLINT
  using namespace fish_protocol;   // NOLINT
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
  using namespace fishbot::driver; // NOLINT
  using namespace fish_protocol;   // NOLINT
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

TEST(TestFishBotDriver, TestCalcuteMotorSpeed) {
  using namespace fishbot::driver; // NOLINT
  using namespace fish_protocol;   // NOLINT
  FishBotConfig fishbot_config;
  ProtocolConfig proto_config;
  proto_config.protocol_type_ = PROTOCOL_TYPE::UDP_SERVER;
  proto_config.udp_server_ip_ = "0.0.0.0";
  proto_config.udp_server_port_ = 3474;
  fishbot_config.protocol_config_ = proto_config;
  FishBotDriver fishbot_driver(fishbot_config);
  sleep(1);
  fishbot_driver.GetMotor()->SendMotorSpeed(0, -static_cast<float>(30) / 100);
  fishbot_driver.GetMotor()->SendMotorSpeed(1, -static_cast<float>(30) / 100);
  sleep(10);
  fishbot_driver.GetMotor()->SendMotorSpeed(0, 0.00);
  fishbot_driver.GetMotor()->SendMotorSpeed(1, 0.00);
  sleep(1);
}

TEST(TestFishBotDriver, TestOdomCalculate) {
  using namespace fishbot::driver; // NOLINT
  using namespace fish_protocol;   // NOLINT
  FishBotConfig fishbot_config;
  ProtocolConfig proto_config;
  proto_config.protocol_type_ = PROTOCOL_TYPE::UDP_SERVER;
  proto_config.udp_server_ip_ = "0.0.0.0";
  proto_config.udp_server_port_ = 3474;
  fishbot_config.protocol_config_ = proto_config;

  MotionModelConfig motion_model_config;
  motion_model_config.model_name = "diff2";
  motion_model_config.diff2_distance = 0.2;
  motion_model_config.diff2_pulse = 3293;
  motion_model_config.diff2_radius = 0.065 / 2;
  fishbot_config.motion_model_config_ = motion_model_config;

  FishBotDriver fishbot_driver(fishbot_config);
  sleep(1);
  fishbot_driver.GetMotor()->SendMotorSpeed(0, 0.00);
  fishbot_driver.GetMotor()->SendMotorSpeed(1, 0.00);
  sleep(5);
  fishbot_driver.GetMotor()->SendMotorSpeed(0, static_cast<float>(-12) / 100);
  fishbot_driver.GetMotor()->SendMotorSpeed(1, static_cast<float>(12) / 100);
  sleep(15);
  fishbot_driver.GetMotor()->SendMotorSpeed(0, 0.00);
  fishbot_driver.GetMotor()->SendMotorSpeed(1, 0.00);
  sleep(1);
}

TEST(TestFishBotDriver, TestMotionModelForawrd) {
  using namespace fishbot::driver; // NOLINT
  using namespace fish_protocol;   // NOLINT
  FishBotConfig fishbot_config;
  ProtocolConfig proto_config;
  proto_config.protocol_type_ = PROTOCOL_TYPE::UDP_SERVER;
  proto_config.udp_server_ip_ = "0.0.0.0";
  proto_config.udp_server_port_ = 3474;
  fishbot_config.protocol_config_ = proto_config;

  MotionModelConfig motion_model_config;
  motion_model_config.model_name = "diff2";
  motion_model_config.diff2_distance = 0.170;
  motion_model_config.diff2_pulse = 3293;
  motion_model_config.diff2_radius = 0.065 / 2;
  fishbot_config.motion_model_config_ = motion_model_config;

  FishBotDriver fishbot_driver(fishbot_config);
  sleep(1);
  fishbot_driver.SetFishBotSpeed(0.0, 1.0);
  sleep(4);
  fishbot_driver.SetFishBotSpeed(0.0, 0.0);

  fishbot_odom_t odom;
  fishbot_speed_t speed;
  fishbot_driver.GetOdom(odom, speed);
  EXPECT_NEAR(odom.yaml, 1.57 * 4, 0.1);
  sleep(1);
}

TEST(TestFishBotDriver, TestMotionModelOdomCallback) {
  using namespace fishbot::driver; // NOLINT
  using namespace fish_protocol;   // NOLINT
  FishBotConfig fishbot_config;
  ProtocolConfig proto_config;
  proto_config.protocol_type_ = PROTOCOL_TYPE::UDP_SERVER;
  proto_config.udp_server_ip_ = "0.0.0.0";
  proto_config.udp_server_port_ = 3474;
  fishbot_config.protocol_config_ = proto_config;

  MotionModelConfig motion_model_config;
  motion_model_config.model_name = "diff2";
  motion_model_config.diff2_distance = 0.170;
  motion_model_config.diff2_pulse = 3293;
  motion_model_config.diff2_radius = 0.065 / 2;
  fishbot_config.motion_model_config_ = motion_model_config;

  FishBotDriver fishbot_driver(fishbot_config);

  fishbot_driver.SetOdomCallback(
      [](const fishbot_odom_t &odom, const fishbot_speed_t &speed) -> void {
        std::cout << odom.x << " " << odom.y << " " << odom.yaml << std::endl;
      });

  sleep(1);
  fishbot_driver.SetFishBotSpeed(0.0, 3.1415926 / 2.0);
  sleep(4);
  fishbot_driver.SetFishBotSpeed(0.0, 0.0);

  fishbot_odom_t odom;
  fishbot_speed_t speed;
  fishbot_driver.GetOdom(odom, speed);
  EXPECT_NEAR(odom.yaml, 1.57 * 4, 0.1);
  sleep(1);
}

TEST(TestFishBotDriver, TestRestartDevice) {
  using namespace fishbot::driver; // NOLINT
  using namespace fish_protocol;   // NOLINT
  FishBotConfig fishbot_config;
  ProtocolConfig proto_config;
  proto_config.protocol_type_ = PROTOCOL_TYPE::SERIAL;
  proto_config.serial_baut_ = 115200;
  proto_config.serial_address_ = "/dev/ttyUSB0";
  fishbot_config.protocol_config_ = proto_config;
  MotionModelConfig motion_model_config;
  motion_model_config.model_name = "diff2";
  motion_model_config.diff2_distance = 0.170;
  motion_model_config.diff2_pulse = 3293;
  motion_model_config.diff2_radius = 0.065 / 2;
  fishbot_config.motion_model_config_ = motion_model_config;

  FishBotDriver fishbot_driver(fishbot_config);

  fishbot_driver.SetOdomCallback(
      [](const fishbot_odom_t &odom, const fishbot_speed_t &speed) -> void {
        std::cout << odom.x << " " << odom.y << " " << odom.yaml << std::endl;
      });

  sleep(1);
  fishbot_driver.SetFishBotSpeed(0.0, 3.1415926 / 2.0);
  sleep(5);
  fishbot_driver.Restart();

  fishbot_odom_t odom;
  fishbot_speed_t speed;
  fishbot_driver.GetOdom(odom, speed);
  sleep(1);
}

TEST(TestFishBotDriver, TestUpdateWifiConfig) {
  using namespace fishbot::driver; // NOLINT
  using namespace fish_protocol;   // NOLINT
  FishBotConfig fishbot_config;
  ProtocolConfig proto_config;
  proto_config.protocol_type_ = PROTOCOL_TYPE::SERIAL;
  proto_config.serial_baut_ = 115200;
  proto_config.serial_address_ = "/dev/ttyUSB0";
  fishbot_config.protocol_config_ = proto_config;
  MotionModelConfig motion_model_config;
  motion_model_config.model_name = "diff2";
  motion_model_config.diff2_distance = 0.170;
  motion_model_config.diff2_pulse = 3293;
  motion_model_config.diff2_radius = 0.065 / 2;
  fishbot_config.motion_model_config_ = motion_model_config;

  FishBotDriver fishbot_driver(fishbot_config);

  fishbot_driver.SetOdomCallback(
      [](const fishbot_odom_t &odom, const fishbot_speed_t &speed) -> void {
        std::cout << odom.x << " " << odom.y << " " << odom.yaml << std::endl;
      });

  proto_data_wifi_config_t wifi_config = {
      .mode = WIFI_MODE_STA,
      .ssid = "JKC",
      .password = "jkc20210106",
  };
  fishbot_driver.GetDevice()->SetWifiConfig(wifi_config);
  sleep(1);
  fishbot_driver.GetDevice()->Restart();
  sleep(10);
  // wifi_config.mode = WIFI_MODE_AP;
  // fishbot_driver.GetDevice()->SetWifiConfig(wifi_config);
  // sleep(1);
  // fishbot_driver.GetDevice()->Restart();
  sleep(10);
}
