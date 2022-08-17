/**
 * @brief 文件描述：设备控制
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-18
 * @copyright 版权所有：FishBot Open Source Organization
 */
#include "fishbot/driver/modules/device.h"

namespace fishbot {
namespace driver {
void Device::Restart(void) {
  ProtoDataFrame data_frame;
  data_frame.UpdateDataHeader(DATA_DEV_CONTROL);
  device_control_.id = DEVICE_MOTION_CONTROL;
  device_control_.operation = DEIVCE_RESTART;
  data_frame.UpdateData<proto_device_control_t>(device_control_);
  ProtoFrame frame({data_frame});
  send_frame_queue_->push(frame);
}

void Device::SetWifiConfig(
    const proto_data_wifi_config_t &proto_data_wifi_config) {
  ProtoDataFrame data_frame;
  data_frame.UpdateDataHeader(DATA_WIFI_CONFIG);
  proto_data_wifi_config_.mode = proto_data_wifi_config.mode;
  sprintf(proto_data_wifi_config_.ssid, "%s",  // NOLINT
          proto_data_wifi_config.ssid);
  sprintf(proto_data_wifi_config_.password, "%s",  // NOLINT
          proto_data_wifi_config.password);
  data_frame.UpdateData<proto_data_wifi_config_t>(proto_data_wifi_config_);
  ProtoFrame frame({data_frame});
  send_frame_queue_->push(frame);
}

void Device::SetProtoConfig(
    const proto_proto_mode_config_t &proto_proto_mode_config) {
  ProtoDataFrame data_frame;
  data_frame.UpdateDataHeader(DATA_PROTO_MODE);
  proto_proto_mode_config_.mode = proto_proto_mode_config.mode;
  proto_proto_mode_config_.bautrate = proto_proto_mode_config.bautrate;
  proto_proto_mode_config_.port = proto_proto_mode_config.port;
  sprintf(proto_proto_mode_config_.ip, "%s",  // NOLINT
          proto_proto_mode_config.ip);
  data_frame.UpdateData<proto_proto_mode_config_t>(proto_proto_mode_config_);
  ProtoFrame frame({data_frame});
  send_frame_queue_->push(frame);
}

}  //  namespace driver
}  //  namespace fishbot
