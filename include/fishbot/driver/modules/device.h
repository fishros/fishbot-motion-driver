/**
 * @brief 文件描述：设备控制
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-17
 * @copyright 版权所有：FishBot Open Source Organization
 */
#ifndef _FISHBOT_DRIVER_MODULEDS_DEVICE_H_
#define _FISHBOT_DRIVER_MODULEDS_DEVICE_H_

#include <memory>
#include <queue>

#include "fishbot/driver/app_protocol/frame.h"
#include "fishbot/driver/app_protocol/proto/proto_define.h"

namespace fishbot {
namespace driver {

class Device {
 private:
  std::queue<ProtoFrame>* send_frame_queue_;
  proto_device_control_t device_control_;

 public:
  Device(std::queue<ProtoFrame>& send_frame_queue) {
    send_frame_queue_ = &send_frame_queue;
  };
  ~Device() = default;

 public:
  void Restart(void);
};

typedef std::shared_ptr<Device> DeviceSharedPtr;

}  // namespace driver
}  // namespace fishbot

#endif  // _FISHBOT_DRIVER_MODULEDS_DEVICE_H_