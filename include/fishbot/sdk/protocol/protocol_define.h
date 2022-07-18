/**
 * @brief 文件描述：待完善
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-17
 * @copyright 版权所有：FishBot Open Source Organization
 */
#ifndef _FISHBOT_SDK_PROTOCOL_PROTOCOL_DEFINE_H_
#define _FISHBOT_SDK_PROTOCOL_PROTOCOL_DEFINE_H_
#include <functional>
#include <iostream>

namespace fishbot {
namespace sdk {

enum class PROTOCOL_TYPE : int {
  NONE = -1,
  SERIAL = 0,
  UDP_SERVER,
  TCP_SERVER,
};

class ProtocolConfig {
 public:
  PROTOCOL_TYPE protocol_type_;
  // serial
  int serial_baut_;
  std::string serial_address_;
  // udp
  int udp_server_port_;
  std::string udp_server_ip_;
  // tcp
  int tcp_server_port_;
  std::string tcp_server_ip_;

  ProtocolConfig& operator=(const ProtocolConfig& config) {
    protocol_type_ = config.protocol_type_;
    serial_baut_ = config.serial_baut_;
    serial_address_ = config.serial_address_;
    udp_server_ip_ = config.udp_server_ip_;
    tcp_server_ip_ = config.tcp_server_ip_;
    tcp_server_port_ = config.tcp_server_port_;
    return *this;
  };

 public:
  ProtocolConfig() = default;
  ~ProtocolConfig() = default;
};

}  // namespace  sdk
}  // namespace fishbot
#endif  // _FISHBOT_SDK_PROTOCOL_PROTOCOL_DEFINE_H_