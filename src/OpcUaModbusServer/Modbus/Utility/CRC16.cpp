/*
   Copyright 2021 Kai Huebl (kai@huebl-sgh.de)

   Lizenziert gemäß Apache Licence Version 2.0 (die „Lizenz“); Nutzung dieser
   Datei nur in Übereinstimmung mit der Lizenz erlaubt.
   Eine Kopie der Lizenz erhalten Sie auf http://www.apache.org/licenses/LICENSE-2.0.

   Sofern nicht gemäß geltendem Recht vorgeschrieben oder schriftlich vereinbart,
   erfolgt die Bereitstellung der im Rahmen der Lizenz verbreiteten Software OHNE
   GEWÄHR ODER VORBEHALTE – ganz gleich, ob ausdrücklich oder stillschweigend.

   Informationen über die jeweiligen Bedingungen für Genehmigungen und Einschränkungen
   im Rahmen der Lizenz finden Sie in der Lizenz.

   Autor: Kai Huebl (kai@huebl-sgh.de)
 */

#include "Modbus/Utility/CRC16.h"

namespace Modbus
{

	CRC16::CRC16(void)
	{
	}

	CRC16::~CRC16(void)
	{
	}

	void
	CRC16::reset(void)
	{
		crc_ccitt_.reset();
	}

	void
	CRC16::process(
		uint8_t byte
	)
	{
		crc_ccitt_.process_byte(byte);
	}

	void
	CRC16::process(
		const boost::asio::streambuf& streambuf,
		uint32_t len
	)
	{
		uint32_t size = streambuf.size();
		std::vector<char> target(size);
		buffer_copy(boost::asio::buffer(target), streambuf.data());

		for (uint32_t idx = 0; idx < len; idx++) {
			crc_ccitt_.process_byte(target[idx]);
		}
	}

	uint16_t
	CRC16::checksum(void)
	{
		return (uint16_t)crc_ccitt_();
	}

	bool
	CRC16::validateChecksum(uint16_t checksum)
	{
		return checksum == this->checksum();
	}

}
