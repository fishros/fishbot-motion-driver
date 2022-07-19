/**
 * @brief 文件描述：待补充
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-07
 * @copyright 版权所有：FishBot Open Source Organization
 */

#include "fishbot/driver/app_protocol/data_frames/base_data_frame.h"

namespace fishbot {
namespace driver {

BaseDataFrame BaseDataFrame::ParseDataFrame(const std::string& raw_data) {
  // BaseDataFrame data_frame(raw_data);
  int data_len = raw_data[0];
  int index = 1;
  int header_size = sizeof(proto_data_header_t);
  for (int i = 0; i < data_len; i++) {
    proto_data_header_t header;
    std::memcpy(reinterpret_cast<char*>(&header), raw_data.data() + index,
                header_size);

    if (header.data_id == DATA_ENCODER) {
      return BaseDataFrame(
          raw_data.substr(index + header_size, header.data_len));
      // return EncoderDataFrame(
      //     raw_data.substr(index + header_size, header.data_len));
    }
  }
  return BaseDataFrame("");
}

}  // namespace driver
}  // namespace fishbot
