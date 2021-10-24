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

#include "Modbus/Modbus/ModbusRTU.h"

namespace Modbus
{

	class ModbusRTUClient
	: public ModbusRTU
	{
	  public:
		using ReadCoilResFunc = std::function<void (void)>;

		ModbusRTUClient(void);
		virtual ~ModbusRTUClient(void);

		bool readCoil(ReadCoilResFunc readCoilResFunc, uint8_t slave, uint16_t address, uint16_t numberCoils);
	};

}

#endif
