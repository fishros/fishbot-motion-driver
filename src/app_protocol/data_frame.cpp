/**
 * @brief 文件描述：待补充
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-07
 * @copyright 版权所有：FishBot Open Source Organization
 */

#include "fishbot/driver/app_protocol/data_frame.h"

#include "fishbot/driver/app_protocol/frame.h"
#include "iostream"

namespace fishbot {
namespace driver {

ProtoDataFrame::ProtoDataFrame(const std::string& raw_data) {
  std::memcpy(reinterpret_cast<char*>(&header_), raw_data.data(),
              sizeof(proto_data_header_t));
  raw_data_ = raw_data;
}

proto_data_header_t ProtoDataFrame::GetHeader() { return header_; }

proto_data_id_t ProtoDataFrame::GetDataId() { return header_.data_id; }

void ProtoDataFrame::UpdateDataHeader(proto_data_id_t data_id,
                                      proto_data_direction_t data_direction,
                                      uint16_t data_len) {
  if (data_len != 0) {
    header_.data_len = data_len;
  }
  header_.data_id = data_id;
  header_.data_direction = data_direction;
}

std::string ProtoDataFrame::GetRawData() {
  raw_data_ = std::string(reinterpret_cast<char*>(&header_),
                          sizeof(proto_data_header_t));
  raw_data_ += pure_raw_data_;
  return raw_data_;
}

std::vector<ProtoDataFrame> ProtoDataFrame::ParseDataFrame(
    const std::string& raw_data) {
  static int data_header_size = sizeof(proto_data_header_t);
  std::vector<ProtoDataFrame> data_frame_queue_;
  int data_len = raw_data[0];
  int index = 1;
  for (int i = 0; i < data_len; i++) {
    proto_data_header_t data_header;
    std::memcpy(reinterpret_cast<char*>(&data_header), raw_data.data() + index,
                data_header_size);
    data_frame_queue_.push_back(ProtoDataFrame(
        raw_data.substr(index, data_header.data_len + data_header_size)));
    index += data_header.data_len + data_header_size;
  }
  return data_frame_queue_;
}

}  // namespace driver
}  // namespace fishbot
