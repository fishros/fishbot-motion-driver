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
}

FishBotDriver::~FishBotDriver() {
  if (protocol_) {
    protocol_->ProtocolDestory();
  }
}

void FishBotDriver::UpdateData() {
  sleep(2);
  // recv data
  while (recv_queue_.size() > 0) {
    ProtoFrame frame = recv_queue_.front();
    recv_queue_.pop();
    std::cout << frame.frame_index_ << std::endl;
  }
  // update data
  // if register -> callback data(?)
}

}  // namespace driver
}  // namespace fishbot
