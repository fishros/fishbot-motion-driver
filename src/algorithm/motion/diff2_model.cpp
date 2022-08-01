/**
 * @brief 文件描述：两轮差速运动学模型
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-31
 * @copyright 版权所有：FishBot Open Source Organization
 */

#include "fishbot/driver/algorithm/motion/diff2_model.h"

#include <cmath>
#include <vector>

namespace fishbot {
namespace driver {

bool Diff2MotionModel::UpdateParams(const MotionModelConfig &motion_config) {
  motion_config_ = motion_config;
  return true;
}

bool Diff2MotionModel::UpdateMotorSpeeds(const std::vector<double> &speeds,
                                         const double &delta_time) {
  // 轮子速度v(米/秒)=电机转速w(弧度/秒)*半径r(米)
  float left_wheel_speed = speeds[0] * motion_config_.diff2_radius;
  float right_wheel_speed = speeds[1] * motion_config_.diff2_radius;
  /* 计算瞬时角速度和线速度 */
  speed_.linear = (left_wheel_speed + right_wheel_speed) / 2.0;
  speed_.angular =
      (right_wheel_speed - left_wheel_speed) / motion_config_.diff2_distance;

  /*更新yaml角角度*/
  odom_.yaml += speed_.angular * delta_time;
  /*更新x和y轴上移动的距离*/
  float delta_distance = speed_.linear * delta_time;
  odom_.x += delta_distance * std::cos(odom_.yaml);
  odom_.y += delta_distance * std::sin(odom_.yaml);

  return true;
}

bool Diff2MotionModel::GetOdomData(fishbot_odom_t &odom) {
  odom = odom_;
  return true;
}

bool Diff2MotionModel::GetSpeedData(fishbot_speed_t &speed) {
  speed = speed_;
  return true;
}

bool Diff2MotionModel::RobotSpeed2MotorSpeed(const fishbot_speed_t &speed,
                                             std::vector<double> &motor_speed) {
  motor_speed.resize(2);
  motor_speed[0] =
      speed.linear - (speed.angular * motion_config_.diff2_distance) / 2.0;
  motor_speed[1] =
      speed.linear + (speed.angular * motion_config_.diff2_distance) / 2.0;

  // 当前仅支持直接发送轮子速度v
  // for (uint32_t i = 0; i < motor_speed.size(); i++) {
  //   motor_speed[i] /= motion_config_.diff2_radius;  // w = v /r;
  // }
  return true;
}

}  // namespace driver
}  // namespace fishbot
