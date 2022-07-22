/**
 * @brief 文件描述：基础数据帧结构类
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-18
 * @copyright 版权所有：FishBot Open Source Organization
 */
#include "fishbot/driver/app_protocol/frame_buffer.h"

#include <iostream>
namespace fishbot {
namespace driver {

int FrameBuffer::PushRawData(const std::string& raw_data) {
  rx_data_.append(raw_data);
  int first = rx_data_.find('\x5A');
  int end = rx_data_.find('\x5A', first + 1);

  if (end - first == 1) {
    first = end;
    end = rx_data_.find('\x5A', first + 1);
  }

  while (first >= 0 && end > first) {
    std::string raw_data = rx_data_.substr(first, end - first + 1);
    // 反转义
    int len = inverse_escape_frame(
        reinterpret_cast<const uint8_t*>(raw_data.data()),
        reinterpret_cast<uint8_t*>(rx_data_temp_), raw_data.size());
    // print_frame_to_hex("raw_data", rx_data_temp_, len);
    ProtoFrame frame = ProtoFrame(std::string(rx_data_temp_, len));
    if (frame.IsValidData()) {
      frames_queue_.push(frame);
    }
    first = rx_data_.find('\x5A', end + 1);
    end = rx_data_.find('\x5A', first + 1);
    // 防止错帧
    if ((first != -1) && (end - first == 1)) {
      first = end;
      end = rx_data_.find('\x5A', first);
    }
  }
  // 擦掉之前的数据
  rx_data_.erase(0, first);
  return 0;
}

int FrameBuffer::GetFrame(ProtoFrame& frame) {
  if (!frames_queue_.empty()) {
    frame = frames_queue_.front();
    frames_queue_.pop();
    return 1;
  }
  return 0;
}

}  // namespace driver
}  // namespace fishbot
