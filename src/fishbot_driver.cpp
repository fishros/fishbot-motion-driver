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

FishBotDriver::FishBotDriver(const FishBotConfig& fishbot_config) {
  fishbot_config_ = fishbot_config;
  switch (fishbot_config.protocol_config_.protocol_type_) {
    case PROTOCOL_TYPE::SERIAL:
      protocol_ =
          std::make_shared<SerialProtocol>(fishbot_config.protocol_config_);
      break;
    case PROTOCOL_TYPE::UDP_SERVER:
      protocol_ =
          std::make_shared<UdpServerProtocol>(fishbot_config.protocol_config_);
      break;
    default:
      break;
  }

  protocol_->SetDataRecvCallback([this](const std::string raw_data) -> void {
    this->frame_buffer_.PushRawData(raw_data);
    ProtoFrame base_frame;
    while (this->frame_buffer_.GetFrame(base_frame)) {
      this->recv_queue_.push(base_frame);
    }
  });

  deal_frame_thread_ = std::thread(std::bind(&FishBotDriver::UpdateData, this));

  motor_ptr_ = std::make_shared<Motor>(send_queue_);
}

FishBotDriver::~FishBotDriver() {
  exit_flag_.store(true);
  deal_frame_thread_.join();
  if (protocol_) {
    protocol_->ProtocolDestory();
  }
}

MotorSharedPtr FishBotDriver::GetMotor() { return motor_ptr_; }

void FishBotDriver::UpdateData() {
  uint32_t frame_count_ = 0;
  while (!exit_flag_.load()) {
    if (!recv_queue_.empty()) {
      ProtoFrame frame = recv_queue_.front();
      recv_queue_.pop();
      frame_count_++;
      // printf("index:%d\n", frame.frame_index_);
      for (ProtoDataFrame data_frame : frame.data_frames_) {
        if (data_frame.GetDataId() == DATA_ENCODER) {
          // std::cout << "motor_encoder:"
          //           << data_frame.GetData<proto_motor_encoder_data_t>()
          //                  .motor_encoder[0]
          //           << std::endl;
          // TODO(小鱼): 完善数据更新.
          // call motor update current speed
          // call odom update pose
          // if register odom callback , call
        }
      }
      // printf("frame_conut=%d\n", frame_count_);
    }

    if (!send_queue_.empty()) {
      protocol_->ProtocolSendRawData(send_queue_.front().GetEscapeRawData());
      send_queue_.pop();
    }
  }
}

}  // namespace driver
}  // namespace fishbot
