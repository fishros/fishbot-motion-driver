/**
 * @brief 文件描述：待完善
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-17
 * @copyright 版权所有：FishBot Open Source Organization
 */
#ifndef _FISHBOT_DRIVER_PROTOCOL_BASE_PROTOCOL_H_
#define _FISHBOT_DRIVER_PROTOCOL_BASE_PROTOCOL_H_
#include <functional>
#include <iostream>
#include <string>

#include "fishbot/driver/protocol/protocol_define.h"

namespace fishbot {
namespace driver {

class BaseProtocol {
 protected:
  std::function<void(const std::string&)> recv_data_callback_;
  ProtocolConfig protocol_config_;

 public:
  BaseProtocol(const ProtocolConfig& protocol_config);
  ~BaseProtocol() = default;

 public:
  virtual int ProtocolSendRawData(const std::string& data) = 0;
  virtual int ProtocolDestory() = 0;
  void SetDataRecvCallback(std::function<void(const std::string&)> callback);
};


}  // namespace  driver
}  // namespace fishbot
#endif  // _FISHBOT_DRIVER_PROTOCOL_BASE_PROTOCOL_H_