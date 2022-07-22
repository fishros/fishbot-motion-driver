#ifndef _COMMUNICATE_SERIAL_COMMUNICATE_H_
#define _COMMUNICATE_SERIAL_COMMUNICATE_H_
#include <unistd.h>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
#include <boost/thread.hpp>
#include <iostream>
#include <string>

#include "fishbot/driver/protocol/base_protocol.h"
#include "fishbot/driver/utils/proto_utils.h"

namespace fishbot {
namespace driver {

class UdpServerProtocol : public BaseProtocol {
 private:
  void _asyncReadSomeData();
  void _initUdpServerProtocol();
  void _recvDataCallback(const boost::system::error_code& error,
                         size_t bytes_transferred);

 public:
  UdpServerProtocol(const ProtocolConfig& protocol_config)
      : BaseProtocol(protocol_config),
        io_service_(),
        socket_(io_service_) {
    _initUdpServerProtocol();
  }
  int ProtocolSendRawData(const std::string& data) override;
  int ProtocolDestory() override;

 private:
  char recv_data_buffer_[1024]{};
  boost::asio::io_service io_service_;
//   boost::asio::serial_port serial_port_;
  boost::asio::ip::udp::socket socket_;
  boost::asio::ip::udp::endpoint remote_endpoint_;
//   boost::array<char, 1> recv_buffer_;
};
}  // namespace driver
}  // namespace fishbot
#endif  // _COMMUNICATE_SERIAL_COMMUNICATE_H_
