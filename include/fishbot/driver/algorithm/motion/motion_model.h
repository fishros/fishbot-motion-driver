#ifndef _FISHBOT_DRIVER_ALGORITHM_MOTION_MOTION_MODEL_H_
#define _FISHBOT_DRIVER_ALGORITHM_MOTION_MOTION_MODEL_H_

#include <iostream>
#include <string>
namespace fishbot {
namespace driver {

typedef struct {
  double linear;
  double angular;
} fishbot_speed_t;

typedef struct {
  double x;
  double y;
  double z;
  double row;
  double pitch;
  double yaml;

} fishbot_odom_t;

class MotionModelConfig {
public:
  std::string model_name; // 模型名称
  float diff2_distance;   // 轮距
  float diff2_radius;     // 轮子半径
  float diff2_pulse; // 脉冲比:轮子转一圈的编码器收到的脉冲数量

  MotionModelConfig &operator=(MotionModelConfig *motion_config) {
    this->model_name = motion_config->model_name;
    this->diff2_distance = motion_config->diff2_distance;
    this->diff2_radius = motion_config->diff2_radius;
    this->diff2_pulse = motion_config->diff2_pulse;
    return *this;
  }

public:
  MotionModelConfig(/* args */) = default;
  ~MotionModelConfig() = default;
};

} // namespace driver
} // namespace fishbot

#endif