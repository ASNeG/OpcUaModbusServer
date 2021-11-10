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
		if (!ModbusPackBase::encode(os)) return false;

		// encode error
		if (ec_) {
			if (!ModbusPackBase::encodeEC(os)) return false;
			return true;
		}

		// encode address
		b[0] = address_ >> 8;
		b[1] = address_ & 0x00ff;
		os.write((char*)b, 2);

		// encode number of inputs
		b[0] = numberInputs_ >> 8;
		b[1] = numberInputs_ & 0x00ff;
		os.write((char*)b, 2);

		return true;
	}

	bool
	ModbusReqReadDiscreteInputs::decode(std::istream& is)
	{

		switch (modbusPackState_)
		{
		  case ModbusPackState::Header:
		  {
			  // decode modbus function
			  if (!ModbusPackBase::decode(is)) return false;

			  if ((modbusFunction() & 0x80) == 0x80) {
				  // receive error body
				  neededSize_ = (uint32_t)1;
				  modbusPackState_ = ModbusPackState::Error;
			  }
			  else {
				  // receive data body
				  neededSize_ = (uint32_t)4;
				  modbusPackState_ = ModbusPackState::Data;
			  }
			  break;
		  }
		  case ModbusPackState::Data:
		  {
			  uint8_t b[2];

			  // decode address
			  is.read((char*)b, 2);
			  address_ = (b[0] << 8) + b[1];

			  // decode number of inputs
			  is.read((char*)b, 2);
			  numberInputs_ = (b[0] << 8) + b[1];

			  neededSize_ = 0;
			  modbusPackState_ = ModbusPackState::Tail;
			  break;
		  }
		  case ModbusPackState::Error:
		  {
			  if (!ModbusPackBase::decodeEC(is)) return false;

			  neededSize_ = 0;
			  modbusPackState_ = ModbusPackState::Tail;
			  break;
		  }
		}

	   return true;
	}

}
