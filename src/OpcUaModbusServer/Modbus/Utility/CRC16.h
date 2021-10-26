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

#ifndef __Modbus_CRC16_h__
#define __Modbus_CRC16_h__

#include <boost/crc.hpp>
#include <boost/asio.hpp>

namespace Modbus
{

	class CRC16
	{
	  public:
		CRC16(void);
		~CRC16(void);

		void reset(void);
		void process(
			const boost::asio::streambuf& streambuf,
			uint32_t len
		);
		uint16_t checksum(void);
		bool validateChecksum(uint16_t checksum);

	  private:
		boost::crc_ccitt_type crc_ccitt_;
	};

}

#endif
