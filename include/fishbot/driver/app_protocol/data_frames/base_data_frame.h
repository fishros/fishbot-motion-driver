/**
 * @brief 文件描述：待补充
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-07
 * @copyright 版权所有：FishBot Open Source Organization
 */
#ifndef _FISHBOT_DRIVER_APP_PROTOCOL_BASE_DATA_FRAME_H_
#define _FISHBOT_DRIVER_APP_PROTOCOL_BASE_DATA_FRAME_H_

#include <string>

#include "fishbot/driver/app_protocol/proto/proto_define.h"

namespace fishbot {
namespace driver {

class BaseDataFrame {
 private:
  proto_data_header_t header;  // 数据头
  std::string data_;           // 数据
 public:
  BaseDataFrame(const std::string& data) { data_ = data; }
  ~BaseDataFrame() = default;
};

}  // namespace driver
}  // namespace fishbot

#endif  // _FISHBOT_DRIVER_APP_PROTOCOL_BASE_DATA_FRAME_H_