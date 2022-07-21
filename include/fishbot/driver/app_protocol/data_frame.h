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
 private:
  proto_data_header_t header_;  // 数据头
  std::string raw_data_;        // 原始数据，包含头
  std::string pure_raw_data_;   // 纯原始数据，不包含头

 public:
  ProtoDataFrame(const std::string& raw_data);
  ProtoDataFrame() = default;
  ~ProtoDataFrame() = default;

  std::string GetRawData();
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
  };
  
  template <typename T>
  void UpdateData(const T& data_struct_t) {
    header_.data_len = sizeof(T);
    pure_raw_data_ = std::string(reinterpret_cast<const char*>(&data_struct_t),
                                 header_.data_len);
  };

  void UpdateDataHeader(proto_data_id_t data_id,
                        proto_data_direction_t data_direction = DATA_TO_FBMC,
                        uint16_t data_len = 0);

 public:
  static std::vector<ProtoDataFrame> ParseDataFrame(
      const std::string& raw_data);
};

}  // namespace driver
}  // namespace fishbot

#endif  // _FISHBOT_DRIVER_APP_PROTOCOL_BASE_DATA_FRAME_H_