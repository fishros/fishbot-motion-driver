#ifndef _COMMUNICATE_SERIAL_COMMUNICATE_H_
#define _COMMUNICATE_SERIAL_COMMUNICATE_H_
#include <unistd.h>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>
#include <boost/asio/serial_port_base.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <communicate/proto_utils.h>
using namespace std;
using namespace boost::asio;

class SerialCommunicate{

private:
  void recv_callback(const boost::system::error_code& error,size_t bytes_transferred)
  {
    // read_msg_[bytes_transferred]=0;
    print_frame_to_hex((uint8_t*)"frame",(uint8_t*)read_msg_,(uint16_t)bytes_transferred);
    read_some();
  }
  void read_some()
  {
    serial_port_.async_read_some(boost::asio::buffer(read_msg_,sizeof(read_msg_)),
			 boost::bind(&SerialCommunicate::recv_callback,this,
				     boost::asio::placeholders::error,
				     boost::asio::placeholders::bytes_transferred));
  }

public:
  SerialCommunicate(const char* dev_name):io_service_(),serial_port_(io_service_,dev_name)
  {
    serial_port_.set_option(boost::asio::serial_port_base::baud_rate(115200));
    serial_port_.set_option(boost::asio::serial_port_base::character_size(8));
    serial_port_.set_option(boost::asio::serial_port_base::stop_bits(serial_port_base::stop_bits::one));
    serial_port_.set_option(boost::asio::serial_port_base::parity(serial_port_base::parity::none));
    serial_port_.set_option(boost::asio::serial_port_base::flow_control(serial_port_base::flow_control::none));
    read_some();
    boost::thread td(boost::bind(&boost::asio::io_service::run,&io_service_));
  }

private:
  char read_msg_[256]{};
  boost::asio::io_service io_service_;
  boost::asio::serial_port serial_port_;
};


#endif // _COMMUNICATE_SERIAL_COMMUNICATE_H_
