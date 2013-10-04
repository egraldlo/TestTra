#include <iostream>
using namespace std;

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

int boost_asio_1(void){
	boost::asio::io_service io;

	boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));

	t.wait();

	std::cout << "Hello, world!\n";
	return 0;
}

void print(const boost::system::error_code& /*e*/)
{
  std::cout << "Hello, world!\n";
}

int boost_asio_2(void)
{
  boost::asio::io_service io;

  boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));
  t.async_wait(print);

  io.run();

  return 0;
}
