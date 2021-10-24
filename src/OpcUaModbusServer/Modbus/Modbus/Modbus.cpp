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
	Modbus::sendReadCoilReq(
		ModbusTrx::SPtr& modbusTrx,
		uint8_t slave,
		uint16_t address,
		uint16_t numberCoils
	)
	{
		uint8_t reqBuf[6];
		reqBuf[0] = slave;
		reqBuf[1] = (uint8_t)ModbusFunction::ReadCoils;
		reqBuf[2] = address >> 8;
	    reqBuf[3] = address & 0x00ff;
	    reqBuf[4] = numberCoils >> 8;
	    reqBuf[5] = numberCoils & 0x00ff;

	    return true;
	    //return sendRequest(modbusTrx, 6, reqBuf);
	}

	void
	Modbus::recvReadCoilRes(ModbusTrx::SPtr& modbusTrx, uint16_t reqLen, uint8_t* reqBuf)
	{
	}

}
