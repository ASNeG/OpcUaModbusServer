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

		switch (modbusStep_)
		{
		  case ModbusStep::Step0:
		  {
			  // decode modbus function
			  is.read((char*)&b, 1);
			  if (b != modbusFunction()) {
				  return false;
			  }

			  // decode number of coil bytes
			  is.read((char*)&b, 1);

			  neededSize_ = (uint32_t)b;
			  modbusStep_ = ModbusStep::Step1;
			  break;
		  }
		  case ModbusStep::Step1:
		  {
			  // decode coil bytes
			  for (uint8_t idx = 0; idx < neededSize_; idx++) {
				  is.read((char*)&b, 1);
				  coils_.push_back(b);
			  }

			  neededSize_ = 0;
			  modbusStep_ = ModbusStep::Step2;
			  break;
		  }
		}

		return true;
	}

	uint32_t
	ModbusResReadCoil::neededSize(void)
	{
		return neededSize_;
	}

	bool
	ModbusResReadCoil::firstPart(void)
	{
		return modbusStep_ == ModbusStep::Step0;
	}

	bool
	ModbusResReadCoil::lastPart(void)
	{
		return modbusStep_ == ModbusStep::Step1;
	}


}
