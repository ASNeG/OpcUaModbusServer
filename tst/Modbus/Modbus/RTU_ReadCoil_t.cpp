#include "unittest.h"
#include <boost/thread/future.hpp>
#include "Modbus/ModbusRTUClient.h"
//#include "Modbus/ModbusRTUServer.h"

using namespace Modbus;

BOOST_AUTO_TEST_SUITE(RTU_ReadCoil_t)

BOOST_AUTO_TEST_CASE(RTU_ReadCoil_)
{
	std::cout << "RTU_ReadCoil_t" << std::endl;
}

BOOST_AUTO_TEST_CASE(RTU_ReadCoil_Open_close)
{
	ModbusRTUClient modbusClient;

	BOOST_REQUIRE(modbusClient.open("/dev/ttyUSB0", 19200, 'E', 8, 1) == true);
	BOOST_REQUIRE(modbusClient.close() == true);
}

BOOST_AUTO_TEST_CASE(RTU_ReadCoil_request_response_async)
{
	ModbusRTUClient modbusClient;

	BOOST_REQUIRE(modbusClient.open("/dev/ttyUSB0", 19200, 'E', 8, 1) == true);

	boost::promise<void> p;
	auto f = p.get_future();

	boost::promise<void>* pp =  &p;
	bool rc = modbusClient.readCoilReq(
		[this, pp] (const boost::system::error_code& ec) mutable {
			std::cout << "handleReadCoilRes" << std::endl;
			pp->set_value();
		},
		1, 0, 8
	);
	BOOST_REQUIRE(rc == true);
	f.get();

	BOOST_REQUIRE(modbusClient.close() == true);
}

BOOST_AUTO_TEST_SUITE_END()