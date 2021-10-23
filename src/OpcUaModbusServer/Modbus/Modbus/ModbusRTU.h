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

#ifndef __Modbus_ModbusRTU_h__
#define __Modbus_ModbusRTU_h__

#include <stdint.h>
#include <functional>
#include <termios.h>
#include "Modbus/Modbus/Modbus.h"

namespace Modbus
{

	class ModbusRTU
	: public Modbus
	{
	  public:
		using TermIOS = struct termios;
		using Speed = speed_t;

		ModbusRTU(void);
		virtual ~ModbusRTU(void);

		bool open(
			const std::string& device,
			uint32_t baud,
			char parity,
			uint8_t dataBits,
			uint8_t stopBits
		);
		bool close(void);

		virtual bool sendReadCoilReq(ModbusTrx::SPtr& modbusTrx, uint8_t* req) override;

	  private:
		int fd_ = -1;
		TermIOS oldTermios_;

	};

}

#endif
