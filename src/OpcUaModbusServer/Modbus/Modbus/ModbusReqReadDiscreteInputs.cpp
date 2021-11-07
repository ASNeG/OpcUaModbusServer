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

#include <Modbus/Modbus/ModbusReqReadDiscreteInputs.h>

namespace Modbus
{

	ModbusReqReadDiscreteInputs::ModbusReqReadDiscreteInputs(void)
	: ModbusPackBase(ModbusFunction::ReadDiscreteInputs)
	{
	}

	ModbusReqReadDiscreteInputs::~ModbusReqReadDiscreteInputs(void)
	{
	}

	void
	ModbusReqReadDiscreteInputs::address(uint16_t address)
	{
		address_ = address;
	}

	uint16_t
	ModbusReqReadDiscreteInputs::address(void)
	{
		return address_;
	}

	void
	ModbusReqReadDiscreteInputs::numberInputs(uint16_t numberInputs)
	{
		numberInputs_ = numberInputs;
	}

	uint16_t
	ModbusReqReadDiscreteInputs::numberInputs(void)
	{
		return numberInputs_;
	}

	bool
	ModbusReqReadDiscreteInputs::encode(std::ostream& os) const
	{
		uint8_t b[2];

		// encode modbus function
		b[0] = modbusFunction();
		os.write((char*)b, 1);

		// encode address
		b[0] = address_ >> 8;
		b[1] = address_ & 0x00ff;
		os.write((char*)b, 2);

		// encode number of coils
		b[0] = numberInputs_ >> 8;
		b[1] = numberInputs_ & 0x00ff;
		os.write((char*)b, 2);

		return true;
	}

	bool
	ModbusReqReadDiscreteInputs::decode(std::istream& is)
	{
		uint8_t b[2];

		// decode modbus function
		is.read((char*)b, 1);
		if (b[0] != modbusFunction()) {
			return false;
		}

		// decode address
		is.read((char*)b, 2);
		address_ = (b[0] << 8) + b[1];

		// decode number of coils
		is.read((char*)b, 2);
		numberInputs_ = (b[0] << 8) + b[1];

		neededSize_ = 0;
		return true;
	}

	uint32_t
	ModbusReqReadDiscreteInputs::neededSize(void)
	{
		return neededSize_;
	}

}
