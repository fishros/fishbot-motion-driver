/**
 * @brief 文件描述：两轮差速运动学模型
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-31
 * @copyright 版权所有：FishBot Open Source Organization
 */
#ifndef _FISHBOT_DRIVER_ALGORITHM_MOTION_DIFF2_MODEL_H_
#define _FISHBOT_DRIVER_ALGORITHM_MOTION_DIFF2_MODEL_H_

#include "fishbot/driver/algorithm/motion/motion_model.h"
#include <vector>

namespace fishbot {
namespace driver {
class Diff2MotionModel {
private:
  fishbot_odom_t odom_;
  fishbot_speed_t speed_;
  MotionModelConfig motion_config_;

public:
  bool UpdateParams(const MotionModelConfig &motion_config);
  bool UpdateMotorSpeeds(const std::vector<double> &speeds,
                         const double &delta_time);
  bool GetOdomData(fishbot_odom_t &odom);
  bool GetSpeedData(fishbot_speed_t &speed);

  bool RobotSpeed2MotorSpeed(const fishbot_speed_t &speed,
                             std::vector<double>& motor_speed);

public:
  Diff2MotionModel(/* args */) = default;
  ~Diff2MotionModel() = default;
};
} // namespace driver
} // namespace fishbot
#endif
