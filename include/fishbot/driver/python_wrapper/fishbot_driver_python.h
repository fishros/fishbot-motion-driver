/**
 * @brief 文件描述：待完成
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-18
 * @copyright 版权所有：FishBot Open Source Organization
 */

#include <boost/python.hpp>

#include "fishbot/driver/fishbot_driver.h"

using namespace fishbot::driver;  // NOLINT
using namespace fish_protocol;    // NOLINT

class FishBotDriverPython {
 private:
  std::shared_ptr<fishbot::driver::FishBotDriver> fishbot_driver_ptr_;
  /*FishBot配置*/
  FishBotConfig fishbot_config_;
  ProtocolConfig protocol_config_;
  MotionModelConfig motion_model_config_;

 public:
  FishBotDriverPython(/* args */) = default;
  ~FishBotDriverPython() = default;
  /*基础配置*/
  bool init();
  void set_protocol_serial(std::string address, int baudrate);
  void set_protocol_udp_client(std::string ip, int port);
  void set_motion_model_diff2(float diff2_distance, float diff2_pulse,
                              float diff2_radius);

  /*设置wifi*/
  void update_wifi_config_sta(std::string ssid, std::string password);
  void update_wifi_config_ap();
  /*设置协议*/
  void update_protocol_config_uart(long baudrate);
  void update_protocol_config_udp_server(long port);
  void update_protocol_config_udp_client(std::string ip, long port);

  void restart();
  void destory();
};
