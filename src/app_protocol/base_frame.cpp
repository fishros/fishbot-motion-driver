/**
 * @brief 文件描述：基础数据帧结构类
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-18
 * @copyright 版权所有：FishBot Open Source Organization
 */

#include "fishbot/driver/app_protocol/base_frame.h"
namespace fishbot {
namespace driver {

BaseFrame::BaseFrame(const std::vector<BaseDataFrame> data_frames) {
  data_frames_ = data_frames;
}

BaseFrame::BaseFrame(const std::string& raw_data) {
  raw_data_ = raw_data;
  _parseRawData();
}

int BaseFrame::_parseRawData() {
  // raw data
  frame_index_ = raw_data_[1];
  target_addr_ = raw_data_[2];
  // 小端模式: 高位在前(低内存)，低位在后(高内存)
  crc16_result_ = raw_data_[raw_data_.size() - 2] & 0xFF;
  crc16_result_ |= ((raw_data_[raw_data_.size() - 3] << 8) & 0xFF00);
  raw_data_frames_ = raw_data_.substr(3, raw_data_.size() - 6);
  data_crc_ = crc16(reinterpret_cast<const uint8_t*>(raw_data_frames_.data()),
                    raw_data_frames_.size());
  std::cout << "data crc:" << data_crc_ << std::endl;
  if(IsValidData())
  {
    data_frame_len_ = raw_data_frames_[0];
  }
  return 0;
}

bool BaseFrame::IsValidData() { return data_crc_ == crc16_result_; }
}  // namespace driver
}  // namespace fishbot
