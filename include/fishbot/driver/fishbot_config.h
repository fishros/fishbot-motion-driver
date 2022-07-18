/**
 * @brief 文件描述：FishBot配置（协议、配置加载等）
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-18
 * @copyright 版权所有：FishBot Open Source Organization
 */
#ifndef _FISHBOT_DRIVER_FISHBOT_CONFIG_H_
#define _FISHBOT_DRIVER_FISHBOT_CONFIG_H_

#include "fishbot/driver/protocol/protocol_define.h"

namespace fishbot {
namespace driver {

class FishBotConfig {
 public:
  ProtocolConfig protocol_config_;
  FishBotConfig& operator=(const FishBotConfig& fishbot_config) {
    protocol_config_ = fishbot_config.protocol_config_;
    return *this;
  };

 public:
  FishBotConfig(/* args */) = default;
  ~FishBotConfig() = default;
};

}  // namespace driver
}  // namespace fishbot

#endif  // _FISHBOT_DRIVER_FISHBOT_CONFIG_H_