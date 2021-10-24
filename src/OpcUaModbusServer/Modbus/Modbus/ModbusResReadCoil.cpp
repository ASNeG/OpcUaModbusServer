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

#include <Modbus/Modbus/ModbusResReadCoil.h>

namespace Modbus
{

	ModbusResReadCoil::ModbusResReadCoil(void)
	: ModbusPackBase(ModbusFunction::ReadCoils)
	{
	}

	ModbusResReadCoil::~ModbusResReadCoil(void)
	{
	}

	void
	ModbusResReadCoil::coils(const std::vector<uint8_t>& coils)
	{
		coils_ = coils;
	}

	std::vector<uint8_t>
	ModbusResReadCoil::coils(void)
	{
		return coils_;
	}

	bool
	ModbusResReadCoil::encode(std::ostream& os) const
	{
		uint8_t b;

		// encode modbus function
		b = modbusFunction();
		os.write((char*)&b, 1);

		// encode number of coil bytes
		b = coils_.size();
		os.write((char*)&b, 1);

		// encode coil bytes
		for (uint8_t idx = 0; idx < coils_.size(); idx++) {
			os.write((char*)&coils_[idx], 1);
		}

		return true;
	}

	bool
	ModbusResReadCoil::decode(std::istream& is)
	{
		uint8_t b;

		// decode modbus function
		is.read((char*)&b, 1);
		if (b != modbusFunction()) {
			return false;
		}

		// decode number of coil bytes
		is.read((char*)&b, 1);
		uint8_t size = b;

		// decode coil bytes
		for (uint8_t idx = 0; idx < size; idx++) {
			is.read((char*)&b, 1);
			coils_.push_back(b);
		}

		return true;
	}

}
