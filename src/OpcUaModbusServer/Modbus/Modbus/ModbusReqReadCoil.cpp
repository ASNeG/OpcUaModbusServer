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

#include <Modbus/Modbus/ModbusReqReadCoil.h>

namespace Modbus
{

	ModbusReqReadCoil::ModbusReqReadCoil(void)
	: ModbusPackBase(ModbusFunction::ReadCoils)
	{
	}

	ModbusReqReadCoil::~ModbusReqReadCoil(void)
	{
	}

	void
	ModbusReqReadCoil::address(uint16_t address)
	{
		address_ = address;
	}

	uint16_t
	ModbusReqReadCoil::address(void)
	{
		return address_;
	}

	void
	ModbusReqReadCoil::numberCoils(uint16_t numberCoils)
	{
		numberCoils_ = numberCoils;
	}

	uint16_t
	ModbusReqReadCoil::numberCoils(void)
	{
		return numberCoils_;
	}

	bool
	ModbusReqReadCoil::encode(std::ostream& os) const
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
		b[0] = numberCoils_ >> 8;
		b[1] = numberCoils_ & 0x00ff;
		os.write((char*)b, 2);

		return true;
	}

	bool
	ModbusReqReadCoil::decode(std::istream& is)
	{
		switch (modbusPackState_)
		{
		  case ModbusPackState::Header:
		  {
			  uint8_t b;

			  // decode modbus function
			  is.read((char*)&b, 1);
			  if (b != modbusFunction()) {

				  if (b == modbusFunction() + 0x80) {
					  decodeEC(is);
				  }
				  else {
					  is.read((char*)&b, 1);
					  ec(ModbusException::IllegalFunction);
				  }

				  return false;
			  }

			  neededSize_ = (uint32_t)4;
			  modbusPackState_ = ModbusPackState::Meta;
			  break;
		  }
		  case ModbusPackState::Meta:
		  {
			  uint8_t b[2];

			  // decode address
			  is.read((char*)b, 2);
			  address_ = (b[0] << 8) + b[1];

			  // decode number of inputs
			  is.read((char*)b, 2);
			  numberCoils_ = (b[0] << 8) + b[1];

			  neededSize_ = 0;
			  modbusPackState_ = ModbusPackState::Tail;
			  break;
		  }
		}

	   return true;
	}

}
