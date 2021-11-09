#include "unittest.h"
#include <string>
#include <sstream>
#include <boost/thread/future.hpp>
#include "Modbus/ModbusRTU/ModbusRTUClient.h"

using namespace Modbus;

BOOST_AUTO_TEST_SUITE(RTU_ReadDiscreteInputs_t)

BOOST_AUTO_TEST_CASE(RTU_ReadDiscreteInputs_)
{
	std::cout << "RTU_ReadDiscreteInputs_t" << std::endl;
}

BOOST_AUTO_TEST_CASE(RTU_ReadDiscreteInputs_request_response_async)
{
	ModbusRTUClient modbusClient;

	BOOST_REQUIRE(modbusClient.open("/dev/ttyUSB0", 19200, 'E', 8, 1) == true);

	boost::promise<void> p;
	auto f = p.get_future();

	boost::promise<void>* pp =  &p;
	bool rc = modbusClient.readDiscreteInputsReq(
		[this, pp] (const boost::system::error_code& ec, std::vector<bool>& inputsVec) mutable {
			std::cout << "handleReadDiscreteInputsRes" << std::endl;
			std::cout << "size=" << inputsVec.size() << std::endl;
			for (auto coil : inputsVec) std::cout << coil << std::endl;
			pp->set_value();
		},
		1, 0, 8
	);
	BOOST_REQUIRE(rc == true);
	f.get();

	BOOST_REQUIRE(modbusClient.close() == true);
}

BOOST_AUTO_TEST_SUITE_END()
