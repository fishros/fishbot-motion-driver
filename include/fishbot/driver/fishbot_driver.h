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
#include <functional>

#include "fish_protocol/fish_protocol.h"
#include "fishbot/driver/algorithm/motion/diff2_model.h"
#include "fishbot/driver/app_protocol/frame.h"
#include "fishbot/driver/app_protocol/frame_buffer.h"
#include "fishbot/driver/fishbot_config.h"
#include "fishbot/driver/modules/motor/motor.h"
#include "fishbot/driver/modules/device.h"

namespace fishbot {
namespace driver {

class FishBotDriver {
 private:
  FishBotConfig fishbot_config_;                           // 机器人配置
  std::shared_ptr<fish_protocol::FishProtocol> protocol_;  // 通信协议
  FrameBuffer frame_buffer_;            // 原始数据缓存池
  std::thread deal_frame_thread_;       // 数据帧处理&回调线程
  std::atomic<bool> exit_flag_{false};  // 退出标志
  std::shared_ptr<Diff2MotionModel> motion_model_;  // 运动模型
  /*callback*/
  std::function<void(const fishbot_odom_t&,const fishbot_speed_t&)> odom_callback_;

 public:
  std::queue<ProtoFrame> recv_queue_;  // 数据帧接收缓存队列
  std::queue<ProtoFrame> send_queue_;  // 数据帧发送缓存队列
  MotorSharedPtr motor_ptr_;
  DeviceSharedPtr device_ptr_;

 public:
  FishBotDriver(const FishBotConfig& fishbot_config);
  ~FishBotDriver();

 public:

  void UpdateData();
  MotorSharedPtr GetMotor();
  void SetFishBotSpeed(const double& linear, const double& angular);

  void GetOdom(fishbot_odom_t& odom, fishbot_speed_t& speed);
  void SetOdomCallback(const std::function<void(const fishbot_odom_t&,const fishbot_speed_t&)> &odom_callback);


  /*
    SetSpeed(linear,angle)
    SetSpeed(int id,int speed)
    UpdateRawData();
    UpdateMotorConfig(int id,pid+tick_scale);
  */
  void Restart(void);
  DeviceSharedPtr GetDevice(void);
};

}  // namespace driver
}  // namespace fishbot

#endif  // _FISHBOT_DRIVER_FISHBOT_DRIVER_H_