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

#ifndef __Modbus_ModbusFunction_h__
#define __Modbus_ModbusFunction_h__

#include <string>
#include <sstream>
#include <functional>

namespace Modbus
{

	enum class ModbusFunction : uint8_t {
		ReadCoils = 0x01,
		ReadDescreteInputs = 0x02,
		ReadHoldingRegisters = 0x03,
		ReadInputRegisters = 0x04,
		WriteSingleCoil = 0x05,
		WriteSingleRegister = 0x06,
		ReadExceptionStatus = 0x07,
		Diagnostics = 0x08,
		GetCommEventCounter = 0x0B,
		GetCommEventLog = 0x0C,
		WriteMultipleCoils = 0x0F,
		WriteMultipleRegisters = 0x10,
		ReportSlaceId = 0x11,
		ReadFileRecord = 0x14,
		WriteFileRecord = 0x15,
		MaskWriteRegisters = 0x16,
		WriteAndReadRegisters = 0x17,
		ReadFifoQueue = 0x18,
		EncapsulatedInterfaceTransport = 0x2B,
	};


	enum class ModbusError : uint8_t {
		x = 0
	};


}

#endif
