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

#include "Modbus/Modbus/ModbusResReadDiscreteInputs.h"

namespace Modbus
{

	ModbusResReadDiscreteInputs::ModbusResReadDiscreteInputs(void)
	: ModbusPackBase(ModbusFunction::ReadDiscreteInputs)
	{
	}

	ModbusResReadDiscreteInputs::~ModbusResReadDiscreteInputs(void)
	{
	}

	void
	ModbusResReadDiscreteInputs::inputs(const std::vector<uint8_t>& inputs)
	{
		inputs_ = inputs;
	}

	std::vector<uint8_t>
	ModbusResReadDiscreteInputs::inputs(void)
	{
		return inputs_;
	}

	bool
	ModbusResReadDiscreteInputs::encode(std::ostream& os) const
	{
		uint8_t b;

		// encode modbus function
		if (!ModbusPackBase::encode(os)) return false;

		// encode error
		if (ec_) {
			if (!ModbusPackBase::encodeEC(os)) return false;
			return true;
		}

		// encode number of input bytes
		b = inputs_.size();
		os.write((char*)&b, 1);

		// encode coil bytes
		for (uint8_t idx = 0; idx < inputs_.size(); idx++) {
			os.write((char*)&inputs_[idx], 1);
		}

		return true;
	}

	bool
	ModbusResReadDiscreteInputs::decode(std::istream& is)
	{
		uint8_t b;

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
				  // receive meta body
				  neededSize_ = (uint32_t)1;
				  modbusPackState_ = ModbusPackState::Meta;
			  }
			  break;
		  }
		  case ModbusPackState::Meta:
		  {

			  // decode number of coil bytes
			  is.read((char*)&b, 1);
			  if ((uint32_t)b > 251) {
				  ec(ModbusException::IllegalDataValue);
				  return false;
			  }

			  neededSize_ = (uint32_t)b;
			  modbusPackState_ = ModbusPackState::Data;
			  break;
		  }
		  case ModbusPackState::Data:
		  {
			  // decode coil bytes
			  for (uint8_t idx = 0; idx < neededSize_; idx++) {
				  is.read((char*)&b, 1);
				  inputs_.push_back(b);
			  }

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
