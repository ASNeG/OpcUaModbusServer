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

#include "boost/make_shared.hpp"
#include "Modbus/Modbus/Modbus.h"
#include "Modbus/Modbus/ModbusTypes.h"

namespace Modbus
{

	Modbus::Modbus(void)
	{
	}

	Modbus::~Modbus(void)
	{
	}

	bool
	Modbus::sendReadCoilReq(uint8_t slave, uint16_t address, uint16_t numberCoils, ReadCoilResp readCoilResp)
	{
		uint8_t req[6];
	    req[0] = slave;
	    req[1] = (uint8_t)ModbusFunction::ReadCoils;
	    req[2] = address >> 8;
	    req[3] = address & 0x00ff;
	    req[4] = numberCoils >> 8;
	    req[5] = numberCoils & 0x00ff;

	    auto modbusTrx = boost::make_shared<ModbusTrx>();
	    return sendReadCoilReq(modbusTrx, req);
	}

}
