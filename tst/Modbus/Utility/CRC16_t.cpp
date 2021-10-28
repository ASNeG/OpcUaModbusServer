#include "unittest.h"
#include <iomanip>
#include "Modbus/Utility/CRC16.h"

using namespace Modbus;

BOOST_AUTO_TEST_SUITE(RTU_CRC16_t)

BOOST_AUTO_TEST_CASE(RTU_CRC16_)
{
	std::cout << "RTU_CRC16_t" << std::endl;
}

BOOST_AUTO_TEST_CASE(RTU_CRC16_process_bytes)
{
	CRC16 crc;

	uint8_t buf[] = {0x01, 0x01, 0x00, 0x00, 0x00, 0x08};

	crc.process(buf, 6);
	BOOST_REQUIRE(crc.checksum() == 0xCC3D);
}

BOOST_AUTO_TEST_SUITE_END()
