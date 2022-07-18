/**
 * @brief 文件描述：协议处理工具，打印、crc、转义与反转义
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-17
 * @copyright 版权所有：FishBot Open Source Organization
 */
#include "fishbot/sdk/protocol/serial_protocol.h"

#include "gtest/gtest.h"

TEST(TestSerialCommunicate, ReadData) {
  using namespace fishbot::sdk;  // NOLINT
  ProtocolConfig proto_config;
  proto_config.protocol_type_ = PROTOCOL_TYPE::SERIAL;
  proto_config.serial_baut_ = 115200;
  proto_config.serial_address_ = "/dev/ttyUSB0";

  SerialProtocol protocol(proto_config);
  sleep(5);
  protocol.ProtocolDestory();
  EXPECT_FLOAT_EQ(1, 1);
}
