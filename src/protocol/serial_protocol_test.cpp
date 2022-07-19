/**
 * @brief 文件描述：串口协议测试
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-17
 * @copyright 版权所有：FishBot Open Source Organization
 */
#include "fishbot/driver/protocol/serial_protocol.h"

#include "gtest/gtest.h"

TEST(TestSerialCommunicate, ReadData) {
  using namespace fishbot::driver;  // NOLINT
  ProtocolConfig proto_config;
  proto_config.protocol_type_ = PROTOCOL_TYPE::SERIAL;
  proto_config.serial_baut_ = 115200;
  proto_config.serial_address_ = "/dev/ttyS12";
  SerialProtocol protocol(proto_config);
  /*
    关于Lambda:
    - [ capture ] ( params ) opt -> ret { body; };
    - 其中 capture 是捕获列表，params 是参数表，opt 是函数选项，ret
    是返回值类型，body是函数体
  */
  int sum_data = 0;
  int* sum_data_p = &sum_data;
  protocol.SetDataRecvCallback([sum_data_p](const std::string& data) -> void {
    *sum_data_p += data.size();
    // std::cout<<"recv data callback, size:"<<data.size()<<std::endl;
    print_frame_to_hex("frame", data.data(), (uint16_t)data.size());
  });
  sleep(3);
  protocol.ProtocolDestory();
  EXPECT_FLOAT_EQ(sum_data > 0, true);
}
