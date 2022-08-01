/**
 * @brief 文件描述：测试
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-17
 * @copyright 版权所有：FishBot Open Source Organization
 */

#include "fishbot/driver/algorithm/motion/diff2_model.h"
#include "gtest/gtest.h"
#define PI 3.1415926

TEST(TestMotionModel, TestDiffModelLinear) {
  using namespace fishbot::driver; // NOLINT
  MotionModelConfig config;
  config.model_name = "diff2";
  config.diff2_distance = 0.2;
  config.diff2_pulse = 3500;
  config.diff2_radius = 0.065 / 2;
  Diff2MotionModel model;
  model.UpdateParams(config);

  fishbot_speed_t target_speed = {.linear = 0.1, .angular = 0.0};
  std::vector<double> speeds;
  model.RobotSpeed2MotorSpeed(target_speed, speeds);
  std::cout << "speed[" << speeds[0] << " ," << speeds[1] << "]" << std::endl;

  model.UpdateMotorSpeeds(speeds, 1.0);
  fishbot_odom_t odom;
  fishbot_speed_t speed;
  model.GetOdomData(odom);
  model.GetSpeedData(speed);
  EXPECT_NEAR(odom.x, 0.1, 0.0001);
}

TEST(TestMotionModel, TestDiffModelAngular) {
  using namespace fishbot::driver; // NOLINT
  MotionModelConfig config;
  config.model_name = "diff2";
  config.diff2_distance = 0.2;
  config.diff2_pulse = 3500;
  config.diff2_radius = 0.065 / 2;
  Diff2MotionModel model;
  model.UpdateParams(config);

  fishbot_speed_t target_speed = {.linear = 0.0, .angular = PI / 2};
  std::vector<double> speeds;
  model.RobotSpeed2MotorSpeed(target_speed, speeds);

  model.UpdateMotorSpeeds(speeds, 1.0);
  fishbot_odom_t odom;
  fishbot_speed_t speed;
  model.GetOdomData(odom);
  model.GetSpeedData(speed);
  EXPECT_NEAR(odom.yaml, PI / 2, 0.0001);
}
