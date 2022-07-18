/**
 * @brief 文件描述：基础数据帧结构类
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-18
 * @copyright 版权所有：FishBot Open Source Organization
 */
#ifndef _FISHBOT_DRIVER_APP_PROTOCOL_BASE_FRAME_H_
#define _FISHBOT_DRIVER_APP_PROTOCOL_BASE_FRAME_H_

#include <cstdint>

#include "fishbot/driver/app_protocol/data_frames/base_data_frame.h"


namespace fishbot {
namespace driver {
class BaseFrame {
 private:
  uint8_t frame_index_;    // 帧序
  uint8_t target_addr_;    // 目标地址
  uint16_t crc16_result_;  // CRC16校验后的结果
  std::vector<BaseDataFrame> data_frams_; // 数据域
 public:
  BaseFrame(/* args */) = default;
  ~BaseFrame() = default;
};

}  // namespace driver
}  // namespace fishbot

#endif  // _FISHBOT_DRIVER_APP_PROTOCOL_BASE_FRAME_H_