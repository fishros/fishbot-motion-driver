/**
 * @brief 文件描述：协议处理工具，打印、crc、转义与反转义
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-17
 * @copyright 版权所有：FishBot Open Source Organization
 */
#include "fishbot/sdk/protocol/base_protocol.h"

namespace fishbot {
namespace sdk {

BaseProtocol::BaseProtocol(const ProtocolConfig& protocol_config) {
  protocol_config_ = protocol_config;
}

void BaseProtocol::SetDataRecvCallback(
    std::function<void(const std::string&)> callback) {
  recv_data_callback_ = callback;
}

}  // namespace sdk
}  // namespace fishbot
