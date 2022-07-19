/**
 * @brief 文件描述：待补充
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-07
 * @copyright 版权所有：FishBot Open Source Organization
 */
#ifndef _FISHBOT_DRIVER_APP_PROTOCOL_ENCODER_DATA_FRAME_H_
#define _FISHBOT_DRIVER_APP_PROTOCOL_ENCODER_DATA_FRAME_H_

#include <cstring>
#include <string>

#include "fishbot/driver/app_protocol/data_frames/base_data_frame.h"

namespace fishbot {
namespace driver {

class EncoderDataFrame : public BaseDataFrame {
 public:
  proto_motor_encoder_data_t encoder_data_;

 public:
  //   EncoderDataFrame(const std::string& data) : BaseDataFrame(data) {
  //     std::memcpy(reinterpret_cast<char*>(&encoder_data_), data.data(),
  //                 data.size());
  //   }
  EncoderDataFrame() = default;
  ~EncoderDataFrame() = default;
};

}  // namespace driver
}  // namespace fishbot

#endif  // _FISHBOT_DRIVER_APP_PROTOCOL_ENCODER_DATA_FRAME_H_