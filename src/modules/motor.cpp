/**
 * @brief 文件描述：电机控制
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-18
 * @copyright 版权所有：FishBot Open Source Organization
 */
#include "fishbot/driver/modules/motor/motor.h"

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

}  // namespace driver
}  // namespace fishbot
