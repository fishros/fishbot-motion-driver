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
#include <thread>

#include "fishbot/driver/app_protocol/frame.h"
#include "fishbot/driver/app_protocol/frame_buffer.h"
#include "fishbot/driver/fishbot_config.h"
#include "fishbot/driver/modules/motor/motor.h"
#include "fishbot/driver/protocol/base_protocol.h"
#include "fishbot/driver/protocol/serial_protocol.h"
#include "fishbot/driver/protocol/udp_server_protocol.h"

namespace fishbot {
namespace driver {

class FishBotDriver {
 private:
  FishBotConfig fishbot_config_;            // 机器人配置
  std::shared_ptr<BaseProtocol> protocol_;  // 通信协议
  FrameBuffer frame_buffer_;                // 原始数据缓存池
  std::thread deal_frame_thread_;           // 数据帧处理&回调线程？
  std::atomic<bool> exit_flag_{false};      // 退出标志

 public:
  std::queue<ProtoFrame> recv_queue_;  // 数据帧接收缓存队列
  std::queue<ProtoFrame> send_queue_;  // 数据帧发送缓存队列
  // Motor motor_;                         // 电机数据处理类
  MotorSharedPtr motor_ptr_;

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
  MotorSharedPtr GetMotor();
};

}  // namespace driver
}  // namespace fishbot

#endif  // _FISHBOT_DRIVER_FISHBOT_DRIVER_H_