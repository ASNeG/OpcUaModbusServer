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

#include "Modbus/ModbusRTU/ModbusRTUException.h"

namespace Modbus
{

	ModbusRTUExceptionCategory::ModbusRTUExceptionCategory(void)
	{
	}

	ModbusRTUExceptionCategory::~ModbusRTUExceptionCategory(void)
	{
	}

	const char*
	ModbusRTUExceptionCategory::name(void) const noexcept
	{
		return "ModbusRTUException";
	}

	std::string
	ModbusRTUExceptionCategory::message(int ev) const
	{
		switch ((ModbusRTUException)ev)
		{
			case ModbusRTUException::Success: return "Success";
			case ModbusRTUException::SlaveInvalid: return "slave invalid";
			case ModbusRTUException::DecoderError: return "decoder error";
			case ModbusRTUException::ChecksumError: return "checksum error";
		}

		std::stringstream ss;
		ss << "unknown error (" << ev << ")";
		return ss.str();
	}

}
