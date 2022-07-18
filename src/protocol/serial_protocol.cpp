/**
 * @brief 文件描述：待添加
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-17
 * @copyright 版权所有：FishBot Open Source Organization
 */

#include "fishbot/sdk/protocol/serial_protocol.h"

namespace fishbot {
namespace sdk {

void SerialProtocol::_initSerialProtocol() {
  boost::system::error_code ec;
  serial_port_.open(protocol_config_.serial_address_, ec);
  std::cout << "ec:" << ec << std::endl;
  serial_port_.set_option(
      boost::asio::serial_port_base::baud_rate(protocol_config_.serial_baut_));
  serial_port_.set_option(boost::asio::serial_port_base::character_size(8));
  serial_port_.set_option(boost::asio::serial_port_base::stop_bits(
      boost::asio::serial_port_base::stop_bits::one));
  serial_port_.set_option(boost::asio::serial_port_base::parity(
      boost::asio::serial_port_base::parity::none));
  serial_port_.set_option(boost::asio::serial_port_base::flow_control(
      boost::asio::serial_port_base::flow_control::none));
  _asyncReadSomeData();
  boost::thread td(boost::bind(&boost::asio::io_service::run, &io_service_));
}

void SerialProtocol::_recvDataCallback(const boost::system::error_code& error,
                                       size_t bytes_transferred) {
  print_frame_to_hex((uint8_t*)"frame",
                     reinterpret_cast<uint8_t*>(recv_data_buffer_),
                     (uint16_t)bytes_transferred);
  _asyncReadSomeData();
}

void SerialProtocol::_asyncReadSomeData() {
  serial_port_.async_read_some(
      boost::asio::buffer(recv_data_buffer_, sizeof(recv_data_buffer_)),
      boost::bind(&SerialProtocol::_recvDataCallback, this,
                  boost::placeholders::_1, boost::placeholders::_2));
}

int SerialProtocol::ProtocolSendRawData(const std::string& data) {
  std::cout << "send" << data.size() << std::endl;
  return 0;
}

int SerialProtocol::ProtocolDestory() {
  io_service_.stop();
  serial_port_.cancel();
  serial_port_.close();
  return 0;
}

}  // namespace sdk
}  // namespace fishbot
