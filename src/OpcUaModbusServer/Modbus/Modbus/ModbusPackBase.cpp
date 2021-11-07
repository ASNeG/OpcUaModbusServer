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

#include "Modbus/Modbus/ModbusPackBase.h"
#include "Modbus/Modbus/ModbusException.h"

namespace Modbus
{

	ModbusPackBase::ModbusPackBase(ModbusFunction modbusFunction)
	: modbusFunction_(modbusFunction)
	{
	}

	ModbusPackBase::~ModbusPackBase(void)
	{
	}

	uint8_t
	ModbusPackBase::modbusFunction(void) const
	{
		return static_cast<uint8_t>(modbusFunction_);
	}

	boost::system::error_code
	ModbusPackBase::ec(void)
	{
		return ec_;
	}

	void
	ModbusPackBase::ec(ModbusException ec)
	{
		MODBUS_EXCEPTION(errorCode, ec)
		ec_ = errorCode;
	}

	bool
	ModbusPackBase::firstPart(void)
	{
		return true;
	}

	bool
	ModbusPackBase::lastPart(void)
	{
		return true;
	}

	bool
	ModbusPackBase::decodeEC(std::istream& is)
	{
		uint8_t ec;

		// decode error code
		is.read((char*)&ec, 1);

		MODBUS_EXCEPTION(errorCode, (uint32_t)ec)
		ec_ = errorCode;

		return true;
	}

}
