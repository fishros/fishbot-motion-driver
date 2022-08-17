/**
 * @brief 文件描述：待完成
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-18
 * @copyright 版权所有：FishBot Open Source Organization
 */
#include "fishbot/driver/python_wrapper/fishbot_driver_python.h"

using namespace fishbot::driver;  // NOLINT
using namespace fish_protocol;    // NOLINT

void FishBotDriverPython::set_protocol_serial(std::string address,
                                              int baudrate) {
  protocol_config_.protocol_type_ = PROTOCOL_TYPE::SERIAL;
  protocol_config_.serial_baut_ = baudrate;
  protocol_config_.serial_address_ = address;
  fishbot_config_.protocol_config_ = protocol_config_;
}

void FishBotDriverPython::set_motion_model_diff2(float diff2_distance,
                                                 float diff2_pulse,
                                                 float diff2_radius) {
  motion_model_config_.model_name = "diff2";
  motion_model_config_.diff2_distance = diff2_distance;
  motion_model_config_.diff2_pulse = diff2_pulse;
  motion_model_config_.diff2_radius = diff2_radius;
  fishbot_config_.motion_model_config_ = motion_model_config_;
}

void FishBotDriverPython::update_wifi_config_sta(std::string ssid,
                                                 std::string password) {
  std::cout << "update wifi config :"
            << "(" << ssid << "," << password << ")" << std::endl;
  proto_data_wifi_config_t wifi_config = {
      .mode = WIFI_MODE_STA,
  };
  sprintf(wifi_config.ssid, "%s", ssid.data());          // NOLINT
  sprintf(wifi_config.password, "%s", password.data());  // NOLINT
  std::cout << "update wifi config2:"
            << "(" << wifi_config.ssid << "," << wifi_config.password << ")"
            << std::endl;
  sprintf(wifi_config.ssid, "%s", ssid.data());
  fishbot_driver_ptr_->GetDevice()->SetWifiConfig(wifi_config);
}

void FishBotDriverPython::update_wifi_config_ap() {
  proto_data_wifi_config_t wifi_config = {
      .mode = WIFI_MODE_AP,
  };
  fishbot_driver_ptr_->GetDevice()->SetWifiConfig(wifi_config);
}

bool FishBotDriverPython::init() {
  fishbot_driver_ptr_ =
      std::make_shared<fishbot::driver::FishBotDriver>(fishbot_config_);
  return true;
}

void FishBotDriverPython::restart() { fishbot_driver_ptr_->Restart(); }

void FishBotDriverPython::destory() {
  // fishbot_driver_ptr_->~FishBotDriver();
  fishbot_driver_ptr_ = nullptr;
}

void FishBotDriverPython::update_protocol_config_uart(long baudrate) {
  // uint32_t bautrate = (uint32_t)baudrate;
  proto_proto_mode_config_t config = {
      .mode = PROTO_MODE_UART,
      .bautrate = (uint32_t)baudrate,
      .port = 3474,
  };
  fishbot_driver_ptr_->GetDevice()->SetProtoConfig(config);
}
void FishBotDriverPython::update_protocol_config_udp_server(long port) {
  proto_proto_mode_config_t config = {
      .mode = PROTO_MODE_WIFI_UDP_SERVER,
      .port = 3474,
  };
  fishbot_driver_ptr_->GetDevice()->SetProtoConfig(config);
}
void FishBotDriverPython::update_protocol_config_udp_client(std::string ip,
                                                            long port) {
  proto_proto_mode_config_t config = {
      .mode = PROTO_MODE_WIFI_UDP_CLIENT,
      .port = (uint16_t)port,
  };
  sprintf(config.ip, "%s", ip.data());  // NOLINT
  fishbot_driver_ptr_->GetDevice()->SetProtoConfig(config);
}

char const *version() { return "v1.0.0.220813"; }

BOOST_PYTHON_MODULE(libfishbot) {
  using namespace boost::python;  // NOLINT
  class_<FishBotDriverPython>("FishBot")
      .def("set_protocol_serial", &FishBotDriverPython::set_protocol_serial)
      .def("set_motion_model_diff2",
           &FishBotDriverPython::set_motion_model_diff2)
      .def("update_wifi_config_ap", &FishBotDriverPython::update_wifi_config_ap)
      .def("init", &FishBotDriverPython::init)
      .def("restart", &FishBotDriverPython::restart)
      .def("destory", &FishBotDriverPython::destory)
      .def("update_protocol_config_uart",
           &FishBotDriverPython::update_protocol_config_uart)
      .def("update_protocol_config_udp_server",
           &FishBotDriverPython::update_protocol_config_udp_server)
      .def("update_protocol_config_udp_client",
           &FishBotDriverPython::update_protocol_config_udp_client)
      .def("update_wifi_config_sta",
           &FishBotDriverPython::update_wifi_config_sta);
  def("version", version);
}
