/**
 * @brief 文件描述：电机控制
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-18
 * @copyright 版权所有：FishBot Open Source Organization
 */
#include "fishbot/driver/modules/motor/motor.h"

#define PI 3.1415926

namespace fishbot {
namespace driver {

void Motor::SendMotorSpeed(int motor_id, const float& speed) {
  ProtoDataFrame data_frame;
  motor_speed_ctrl_.motor_speed[motor_id] = speed * 1000;  // rau/s->rau/ms
  data_frame.UpdateDataHeader(DATA_SPEED);
  data_frame.UpdateData<proto_motor_speed_ctrl_data_t>(motor_speed_ctrl_);
  // ProtoFrame
  ProtoFrame frame({data_frame});
  // push queue
  send_frame_queue_->push(frame);
}

void Motor::SendSpeed(std::vector<double>& speed) {
  ProtoDataFrame data_frame;
  for (uint16_t i = 0; i < speed.size(); i++) {
    motor_speed_ctrl_.motor_speed[i] = speed[i] * 1000;  // rau/s->rau/ms
  }
  data_frame.UpdateDataHeader(DATA_SPEED);
  data_frame.UpdateData<proto_motor_speed_ctrl_data_t>(motor_speed_ctrl_);
  ProtoFrame frame({data_frame});
  send_frame_queue_->push(frame);
}

void Motor::UpdateEncoder(const std::vector<int32_t> encoder,
                          const double& delta_time) {
  if (last_encoder_.size() == 0) {
    current_speeds_.resize(encoder.size());
    last_encoder_ = encoder;
    return;
  }

  for (uint16_t i = 0; i < encoder.size(); i++) {
    int32_t count = encoder[i] - last_encoder_[i];
    std::cout << "delta_time:" << delta_time << " count:" << count << std::endl;
    current_speeds_[i] = static_cast<double>(count) * 2 * PI /
                         (motor_reduce_scale_ * delta_time);
    last_encoder_[i] = encoder[i];
  }
}

void Motor::GetMotorSpeed(std::vector<double>& speed) {
  speed = current_speeds_;
}

void Motor::UpdateMotorParam(const double& motor_reduce_scale) {
  motor_reduce_scale_ = motor_reduce_scale;
}
}  // namespace driver
}  // namespace fishbot
