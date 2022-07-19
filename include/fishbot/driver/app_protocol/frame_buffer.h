/**
 * @brief 文件描述：数据帧buffer类，输入原生字符，输出数据帧
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-18
 * @copyright 版权所有：FishBot Open Source Organization
 */
#ifndef _FISHBOT_DRIVER_APP_PROTOCOL_FRAME_BUFFER_H_
#define _FISHBOT_DRIVER_APP_PROTOCOL_FRAME_BUFFER_H_

#include <cstdint>
#include <queue>
#include <vector>

#include "fishbot/driver/app_protocol/base_frame.h"

namespace fishbot {
namespace driver {
class FrameBuffer {
 private:
  std::string rx_data_;
  char rx_data_temp_[1024];
  std::queue<BaseFrame> frames_queue_;

 public:
  int PushRawData(const std::string& raw_data);
  int GetFrame(BaseFrame& frame);

 public:
  FrameBuffer() = default;
  ~FrameBuffer() = default;
};

}  // namespace driver
}  // namespace fishbot

#endif  // _FISHBOT_DRIVER_APP_PROTOCOL_FRAME_BUFFER_H_