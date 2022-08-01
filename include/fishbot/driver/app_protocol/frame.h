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
#include <cstring>
#include <iostream>
#include <vector>

#include "fishbot/driver/app_protocol/data_frame.h"
#include "fishbot/driver/app_protocol/proto/proto_define.h"
#include "fishbot/driver/utils/proto_utils.h"

namespace fishbot {
namespace driver {
class ProtoFrame {
 private:
  int _parseRawData();

 public:
  std::string raw_data_;         // 原始数据
  uint8_t frame_index_;          // 帧序
  uint8_t target_addr_;          // 目标地址
  uint16_t crc16_result_;        // 数据记录的CRC16校验结果
  uint16_t data_crc_;            // 对原始数据进行CRC16校验后的结果
  uint16_t data_frame_len_;      // 数据帧的个数
  std::string raw_data_frames_;  // 数据域原始数据
  std::vector<ProtoDataFrame> data_frames_;  // 数据域

 public:
  bool IsValidData();
  std::string GetRawData();
  /**
   * @brief 获取数据帧并转义
   *
   * @return std::string
   */
  std::string GetEscapeRawData();
  static uint8_t GetSendFrameIndex();
  

 public:
  ProtoFrame(const std::vector<ProtoDataFrame> data_frames);
  ProtoFrame(const std::string& raw_data);
  ProtoFrame() = default;
  ~ProtoFrame() = default;
  ProtoFrame& operator=(const ProtoFrame& base_frame) {
    raw_data_ = base_frame.raw_data_;
    frame_index_ = base_frame.frame_index_;
    target_addr_ = base_frame.target_addr_;
    crc16_result_ = base_frame.crc16_result_;
    data_crc_ = base_frame.data_crc_;
    data_frame_len_ = base_frame.data_frame_len_;
    raw_data_frames_ = base_frame.raw_data_frames_;
    data_frames_ = base_frame.data_frames_;
    return *this;
  }
};

}  // namespace driver
}  // namespace fishbot

#endif  // _FISHBOT_DRIVER_APP_PROTOCOL_BASE_FRAME_H_