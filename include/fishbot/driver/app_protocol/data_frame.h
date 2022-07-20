/**
 * @brief 文件描述：待补充
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-07
 * @copyright 版权所有：FishBot Open Source Organization
 */
#ifndef _FISHBOT_DRIVER_APP_PROTOCOL_DATA_FRAME_H_
#define _FISHBOT_DRIVER_APP_PROTOCOL_DATA_FRAME_H_

#include <cstring>
#include <string>
#include <vector>

#include "fishbot/driver/app_protocol/proto/proto_define.h"

namespace fishbot {
namespace driver {

class ProtoDataFrame {
 public:
  proto_data_header_t header_;  // 数据头
  std::string raw_data_;        // 原始数据
 public:
  ProtoDataFrame(const std::string& raw_data);
  ProtoDataFrame() = default;
  ~ProtoDataFrame() = default;
  std::string GetRawData() { return raw_data_; };

  proto_data_header_t GetHeader();
  proto_data_id_t GetDataId();

  /**
   * @brief 获取对应ID类型的数据
   *
   * @tparam T
   * @return T
   */
  template <typename T>
  T GetData() {
    T data;
    std::memcpy(reinterpret_cast<char*>(&data),
                raw_data_.data() + sizeof(proto_data_header_t),
                raw_data_.size() - sizeof(proto_data_header_t));
    return data;
  }

  template <typename T>
  void UpdateData(const T&);

 public:
  static std::vector<ProtoDataFrame> ParseDataFrame(const std::string& raw_data);
};

}  // namespace driver
}  // namespace fishbot

#endif  // _FISHBOT_DRIVER_APP_PROTOCOL_BASE_DATA_FRAME_H_