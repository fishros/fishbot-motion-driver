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
  std::vector<double> current_speeds_;
  double last_update_time_;
  double motor_reduce_scale_{3293}; /*电机脉冲比，转一圈编码器所产生的脉冲数量*/
  std::vector<int32_t> last_encoder_;

 public:
  Motor(std::queue<ProtoFrame>& send_frame_queue) {
    send_frame_queue_ = &send_frame_queue;
  };
  ~Motor() = default;

 public:
  void UpdateMotorParam(const double& motor_reduce_scale);
  void UpdateEncoder(const std::vector<int32_t> encoder, const double& time);

  /**
   * @brief 获取电机的速度
   *
   * @param speed 速度数据
   */
  void GetMotorSpeed(std::vector<double>& speed);
  void SendSpeed(std::vector<double>& speed);
  void SendMotorSpeed(int motor_id, const float& speed);
};

typedef std::shared_ptr<Motor> MotorSharedPtr;

}  // namespace driver
}  // namespace fishbot

#endif  // _FISHBOT_DRIVER_MODULEDS_MOTOR_H_