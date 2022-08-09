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
void Device::Restart(void)
{
  ProtoDataFrame data_frame;
  data_frame.UpdateDataHeader(DATA_DEV_CONTROL);
  device_control_.id = DEVICE_MOTION_CONTROL;
  device_control_.operation = DEIVCE_RESTART;
  data_frame.UpdateData<proto_device_control_t>(device_control_);
  ProtoFrame frame({data_frame});
  send_frame_queue_->push(frame);
}

}  // namespace driver
}  // namespace fishbot
