/**
 * @brief 文件描述：FishBot驱动入口类
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-18
 * @copyright 版权所有：FishBot Open Source Organization
 */
#include "fishbot/driver/fishbot_driver.h"

namespace fishbot {
namespace driver {

FishBotDriver::FishBotDriver(const FishBotConfig &fishbot_config) {
  using namespace fish_protocol; // NOLINT
  fishbot_config_ = fishbot_config;
  protocol_ = GetProtocolByConfig(fishbot_config.protocol_config_);
  protocol_->SetDataRecvCallback([this](const std::string raw_data) -> void {
    this->frame_buffer_.PushRawData(raw_data);
    ProtoFrame base_frame;
    while (this->frame_buffer_.GetFrame(base_frame)) {
      this->recv_queue_.push(base_frame);
    }
  });

  /*电机控制*/
  motor_ptr_ = std::make_shared<Motor>(send_queue_);
  motor_ptr_->UpdateMotorParam(fishbot_config.motion_model_config_.diff2_pulse);
  /* 运动学部分 */
  motion_model_ = std::make_shared<Diff2MotionModel>();
  motion_model_->UpdateParams(fishbot_config_.motion_model_config_);
  /*设备控制*/
  device_ptr_ = std::make_shared<Device>(send_queue_);

  deal_frame_thread_ = std::thread(std::bind(&FishBotDriver::UpdateData, this));
}

FishBotDriver::~FishBotDriver() {
  exit_flag_.store(true);
  deal_frame_thread_.join();
  if (protocol_) {
    protocol_->ProtocolDestory();
  }
}


void FishBotDriver::Restart(void)
{
  device_ptr_->Restart();
}


DeviceSharedPtr FishBotDriver::GetDevice(void)
{
  return device_ptr_;
}

MotorSharedPtr FishBotDriver::GetMotor() { return motor_ptr_; }

void FishBotDriver::GetOdom(fishbot_odom_t &odom, fishbot_speed_t &speed) {
  motion_model_->GetSpeedData(speed);
  motion_model_->GetOdomData(odom);
}

void FishBotDriver::SetFishBotSpeed(const double &linear,
                                    const double &angular) {
  fishbot_speed_t speed = {
      .linear = linear,
      .angular = angular,
  };
  std::vector<double> motor_speed;
  motion_model_->RobotSpeed2MotorSpeed(speed, motor_speed);
  motor_ptr_->SendSpeed(motor_speed);
}

void FishBotDriver::UpdateData() {
  uint32_t frame_count_ = 0;
  auto current_time = std::chrono::steady_clock::now();
  auto last_time = std::chrono::steady_clock::now();
  fishbot_speed_t fishbot_speed;
  fishbot_odom_t fishbot_odom;
  float delta_time =
      std::chrono::duration<double>(current_time - last_time).count();

  while (!exit_flag_.load()) {
    if (!recv_queue_.empty()) {
      ProtoFrame frame = recv_queue_.front();
      recv_queue_.pop();
      frame_count_++;
      current_time = std::chrono::steady_clock::now();
      delta_time =
          std::chrono::duration<double>(current_time - last_time).count();
      for (ProtoDataFrame data_frame : frame.data_frames_) {
        if (data_frame.GetDataId() == DATA_ENCODER) {
          // std::cout << "motor_encoder:"
          //           << data_frame.GetData<proto_motor_encoder_data_t>()
          //                  .motor_encoder[0]
          //           << std::endl;
          proto_motor_encoder_data_t encoder_data =
              data_frame.GetData<proto_motor_encoder_data_t>();

          // 1.call motor update current speed
          motor_ptr_->UpdateEncoder(
              {encoder_data.motor_encoder[0], encoder_data.motor_encoder[1]},
              delta_time);
          std::vector<double> motor_speed;
          motor_ptr_->GetMotorSpeed(motor_speed);

          // 2.call odom update pose
          motion_model_->UpdateMotorSpeeds(motor_speed, delta_time);

          // 3.if register odom callback , call

          motion_model_->GetSpeedData(fishbot_speed);
          motion_model_->GetOdomData(fishbot_odom);
          if (odom_callback_) {
            odom_callback_(fishbot_odom, fishbot_speed);
          }
          // std::cout << "fishbot_odom(" << fishbot_odom.x << ","
          //           << fishbot_odom.y << "," << fishbot_odom.yaml << ")"
          //           << std::endl;
        } else if (data_frame.GetDataId() == DATA_IMU) {
          // std::cout << data_frame.GetData<proto_imu_data_t>().euler[2]
          //           << std::endl;
        }
      }
      last_time = current_time;
    }

    if (!send_queue_.empty()) {
      protocol_->ProtocolSendRawData(send_queue_.front().GetEscapeRawData());
      std::cout<<send_queue_.front().GetEscapeRawData()<<std::endl;
      send_queue_.pop();
    }
  }
}

void FishBotDriver::SetOdomCallback(
    const std::function<void(const fishbot_odom_t &, const fishbot_speed_t &)>
        &odom_callback) {
  odom_callback_ = odom_callback;
}

}  // namespace driver
}  // namespace fishbot
