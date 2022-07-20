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
  std::cout << "contruct ProtoDataFrame with:" << raw_data.size() << std::endl;
  raw_data_ = raw_data;
}

proto_data_header_t ProtoDataFrame::GetHeader() { return header_; }

std::vector<ProtoDataFrame> ProtoDataFrame::ParseDataFrame(
    const std::string& raw_data) {
  // ProtoDataFrame data_frame(raw_data);
  std::vector<ProtoDataFrame> data_frame_queue_;
  int data_len = raw_data[0];
  int index = 1;
  int header_size = sizeof(proto_data_header_t);
  for (int i = 0; i < data_len; i++) {
    // ProtoDataFrame data_frame(raw_data.substr(index,));
    // std::memcpy(reinterpret_cast<char*>(&data_frame.header_), raw_data.data() + index,
    //             header_size);

    // if (header.data_id == DATA_ENCODER) {
    //   EncoderDataFrame frame = EncoderDataFrame(raw_data.substr(
    //       index, sizeof(proto_data_header_t) + header.data_len));
    //   data_frame_queue_.push_back(frame);
    // }
  }
  return data_frame_queue_;
}

}  // namespace driver
}  // namespace fishbot
