/**
 * @brief 文件描述：基础数据帧结构类
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-18
 * @copyright 版权所有：FishBot Open Source Organization
 */

#include "fishbot/driver/app_protocol/frame.h"
namespace fishbot {
namespace driver {

ProtoFrame::ProtoFrame(const std::vector<ProtoDataFrame> data_frames) {
  data_frames_ = data_frames;
  frame_index_ = GetSendFrameIndex();
  target_addr_ = DATA_TARGET_ADDR_FBMC;  // 目标地址运动控制板
  data_frame_len_ = data_frames.size();
  raw_data_frames_ = std::string(data_frame_len_, 1);
  for (ProtoDataFrame data_frame : data_frames) {
    raw_data_frames_.append(data_frame.GetRawData().data(),
                            data_frame.GetRawData().size());
  }
  data_crc_ = crc16(reinterpret_cast<const uint8_t*>(raw_data_frames_.data()),
                    raw_data_frames_.size());
  crc16_result_ = data_crc_;

  raw_data_.erase();
  char data_temp[1024];
  int frame_len = 0;
  data_temp[frame_len++] = 0x5A;
  data_temp[frame_len++] = frame_index_;
  data_temp[frame_len++] = target_addr_;
  std::memcpy(data_temp + frame_len, raw_data_frames_.data(),
              raw_data_frames_.size());
  frame_len += raw_data_frames_.size();
  data_temp[frame_len++] = crc16_result_ >> 8;
  data_temp[frame_len++] = crc16_result_;
  data_temp[frame_len++] = 0x5A;
  raw_data_ = std::string(data_temp, frame_len);
}

ProtoFrame::ProtoFrame(const std::string& raw_data) {
  raw_data_ = raw_data;
  _parseRawData();
}

uint8_t ProtoFrame::GetSendFrameIndex() {
  static uint8_t send_frame_index = 0;  // 发送数据帧的计数
  return send_frame_index++;
}

std::string ProtoFrame::GetRawData() { return raw_data_; }

std::string ProtoFrame::GetEscapeRawData() {
  uint8_t temp_data[1024];  // 临时
  int frame_size =
      escape_frame(reinterpret_cast<const uint8_t*>(raw_data_.data()),
                   temp_data, raw_data_.size());
  return std::string(reinterpret_cast<char*>(temp_data), frame_size);
}

int ProtoFrame::_parseRawData() {
  frame_index_ = raw_data_[1];  // 数据帧号
  target_addr_ = raw_data_[2];  // 目标地址
  SET_SUB_BYTES1(crc16_result_, raw_data_[raw_data_.size() - 2]);
  SET_SUB_BYTES2(crc16_result_, raw_data_[raw_data_.size() - 3]);
  // 获取原生数据域
  raw_data_frames_ = raw_data_.substr(3, raw_data_.size() - 6);
  data_crc_ = crc16(reinterpret_cast<const uint8_t*>(raw_data_frames_.data()),
                    raw_data_frames_.size());
  // 有效则扔进去
  if (IsValidData()) {
    data_frame_len_ = raw_data_frames_[0];
    data_frames_ = ProtoDataFrame::ParseDataFrame(raw_data_frames_);
  } else {
    print_frame_to_hex("errorcrc frame", raw_data_.data(), raw_data_.size());
    return -1;
  }
  return 0;
}

bool ProtoFrame::IsValidData() { return data_crc_ == crc16_result_; }
}  // namespace driver
}  // namespace fishbot
