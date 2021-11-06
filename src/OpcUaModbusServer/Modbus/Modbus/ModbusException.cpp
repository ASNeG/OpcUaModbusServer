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

#include "Modbus/Modbus/ModbusException.h"

namespace Modbus
{

	ModbusExceptionCategory::ModbusExceptionCategory(void)
	{
	}

	ModbusExceptionCategory::~ModbusExceptionCategory(void)
	{
	}

	const char*
	ModbusExceptionCategory::name(void) const noexcept
	{
		return "ModbusException";
	}

	std::string
	ModbusExceptionCategory::message(int ev) const
	{
		switch ((ModbusException)ev)
		{
			case ModbusException::Success: return "Success";
			case ModbusException::IllegalFunction: return "Illegal Function";
			case ModbusException::IllegalDataAddress: return "Illegal Data Address";
			case ModbusException::IllegalDataValue: return "Illegal Data Value";
			case ModbusException::SlaveDeviceFailure: return "Slave Device Failure";
			case ModbusException::Acknowledge: return "Acknowledge";
			case ModbusException::SlaveDeviceBuy: return "Slave Device Busy";
			case ModbusException::MemoryParityError: return "Memory Parity Error";
			case ModbusException::GatewayPathUnavailable: return "Gateway Path Unavailable";
			case ModbusException::GatewayTargetDeviceFailedToRespond: return "Gateway Target Device Failed To Respond";
		}

		std::stringstream ss;
		ss << "unknown error (" << ev << ")";
		return ss.str();
	}

}
