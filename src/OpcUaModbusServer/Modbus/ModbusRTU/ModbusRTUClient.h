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

#ifndef __Modbus_ModbusRTUClient_h__
#define __Modbus_ModbusRTUClient_h__

#include <stdint.h>
#include <functional>

#include "Modbus/ModbusRTU/ModbusRTU.h"
#include "Modbus/ModbusRTU/ModbusRTUClientTrx.h"

namespace Modbus
{

	class ModbusRTUClient
	: public ModbusRTU
	{
	  public:
		ModbusRTUClient(void);
		virtual ~ModbusRTUClient(void);

		bool readCoilReq(ReadCoilResFunc readCoilResFunc, uint8_t slave, uint16_t address, uint16_t numberCoils);

	  private:

		void handleReadCoilRes(const boost::system::error_code& ec, const ModbusRTUTrx::SPtr& modbusRTUTrx);
	};

}

#endif
