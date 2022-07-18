/**
 * @brief 文件描述：FishBot驱动入口类
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-18
 * @copyright 版权所有：FishBot Open Source Organization
 */
#ifndef _FISHBOT_DRIVER_FISHBOT_DRIVER_H_
#define _FISHBOT_DRIVER_FISHBOT_DRIVER_H_

#include <memory>

#include "fishbot/driver/fishbot_config.h"
#include "fishbot/driver/protocol/base_protocol.h"
#include "fishbot/driver/protocol/serial_protocol.h"

namespace fishbot {
namespace driver {

class FishBotDriver {
 private:
  FishBotConfig fishbot_config_;
  std::shared_ptr<BaseProtocol> protocol_;
    
private:
 public:
  FishBotDriver(const FishBotConfig& fishbot_config);
  ~FishBotDriver();
};

}  // namespace driver
}  // namespace fishbot

#endif  // _FISHBOT_DRIVER_FISHBOT_DRIVER_H_