/**
 * @brief 文件描述：待补充
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-07
 * @copyright 版权所有：FishBot Open Source Organization
 */
#ifndef _FISHBOT_DRIVER_APP_PROTOCOL_BASE_DATA_FRAME_H_
#define _FISHBOT_DRIVER_APP_PROTOCOL_BASE_DATA_FRAME_H_

#include <cstring>
#include <string>

#include "fishbot/driver/app_protocol/proto/proto_define.h"
#include "fishbot/driver/app_protocol/data_frames/encoder_data_frame.h"

namespace fishbot {
namespace driver {

class BaseDataFrame {
 public:
  proto_data_header_t header_;  // 数据头
  std::string raw_data_;        // 原始数据
 public:
  BaseDataFrame(const std::string& data) { raw_data_ = data;
   }
  ~BaseDataFrame() = default;

 public:
  static BaseDataFrame ParseDataFrame(const std::string& raw_data);
};

}  // namespace driver
}  // namespace fishbot

#endif  // _FISHBOT_DRIVER_APP_PROTOCOL_BASE_DATA_FRAME_H_