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

  deal_frame_thread_ = std::thread(std::bind(&FishBotDriver::UpdateData, this));
}

FishBotDriver::~FishBotDriver() {
  exit_flag_.store(true);
  deal_frame_thread_.join();
  if (protocol_) {
    protocol_->ProtocolDestory();
  }
}

void FishBotDriver::UpdateData() {
  while (!exit_flag_.load()) {
    if (recv_queue_.size() > 0) {
      ProtoFrame frame = recv_queue_.front();
      recv_queue_.pop();
      printf("index:%d\n", frame.frame_index_);
      for (ProtoDataFrame data_frame : frame.data_frames_) {
        if (data_frame.GetDataId() == DATA_ENCODER) {
          std::cout << "motor_encoder:"
                    << data_frame.GetData<proto_motor_encoder_data_t>()
                           .motor_encoder[0]
                    << std::endl;
        }
      }
    }
  }
  // update data
  // if register -> callback data(?)
}

}  // namespace driver
}  // namespace fishbot
