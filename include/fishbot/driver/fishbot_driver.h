/**
 * @brief 文件描述：FishBot驱动入口类
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-18
 * @copyright 版权所有：FishBot Open Source Organization
 */
#ifndef _FISHBOT_DRIVER_FISHBOT_DRIVER_H_
#define _FISHBOT_DRIVER_FISHBOT_DRIVER_H_

#include <memory>
#include <queue>

#include "fishbot/driver/fishbot_config.h"
#include "fishbot/driver/protocol/base_protocol.h"
#include "fishbot/driver/protocol/serial_protocol.h"
#include "fishbot/driver/app_protocol/frame.h"
#include "fishbot/driver/app_protocol/frame_buffer.h"

namespace fishbot {
namespace driver {

class FishBotDriver {
 private:
  FishBotConfig fishbot_config_;
  std::shared_ptr<BaseProtocol> protocol_;
  FrameBuffer frame_buffer_;
  std::queue<ProtoFrame> recv_queue_;
  std::queue<ProtoFrame> send_queue_;
    
private:
 public:
  FishBotDriver(const FishBotConfig& fishbot_config);
  ~FishBotDriver();
  public:
    void UpdateData();
  /*
    SetSpeed(linear,angle)
    xyz,rxryrz = GetOdom()
    GetImu()
  */

  /*
    ResetOdom()
    UpdateConfig()
    GetPose()
    GetSpeed()
  */
  void Odom();

  /*
    GetImu()
    GetMotion()
    Calibration()
  */
  void IMU();

  /*
    SetSpeed(linear,angle)
    SetSpeed(int id,int speed)
    UpdateRawData();
    UpdateMotorConfig(int id,pid+tick_scale);
  */
  void Motor();
};

}  // namespace driver
}  // namespace fishbot

#endif  // _FISHBOT_DRIVER_FISHBOT_DRIVER_H_