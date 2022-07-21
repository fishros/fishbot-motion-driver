/**
 * @brief 文件描述：FishBot驱动
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-17
 * @copyright 版权所有：FishBot Open Source Organization
 */
#ifndef _FISHBOT_DRIVER_MODULEDS_MOTOR_H_
#define _FISHBOT_DRIVER_MODULEDS_MOTOR_H_

#include <memory>
#include <queue>

#include "fishbot/driver/app_protocol/frame.h"
#include "fishbot/driver/app_protocol/proto/proto_define.h"

namespace fishbot {
namespace driver {

class Motor {
 private:
  std::queue<ProtoFrame>* send_frame_queue_;
  proto_motor_speed_ctrl_data_t motor_speed_ctrl_;

 public:
  Motor(std::queue<ProtoFrame>& send_frame_queue) {
    send_frame_queue_ = &send_frame_queue;
  };
  ~Motor() = default;

 public:
  void UpdateEncoder(int32_t encoder_data[]);
  void SendSpeed(const float& linear_speed, const float& angular_speed);
  void SendMotorSpeed(int motor_id, const float& speed);
};

typedef std::shared_ptr<Motor> MotorSharedPtr;

}  // namespace driver
}  // namespace fishbot

#endif  // _FISHBOT_DRIVER_MODULEDS_MOTOR_H_