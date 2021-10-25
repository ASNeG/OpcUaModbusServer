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

#ifndef __Modbus_ModbusResReadCoil_h__
#define __Modbus_ModbusResReadCoil_h__

#include <vector>
#include "Modbus/Modbus/ModbusPackBase.h"

namespace Modbus
{

	class ModbusResReadCoil
	: public ModbusPackBase
	{
	  public:

		using SPtr = boost::shared_ptr<ModbusResReadCoil>;

		ModbusResReadCoil(void);
		virtual ~ModbusResReadCoil(void);

		void coils(const std::vector<uint8_t>& coils);
		std::vector<uint8_t> coils(void);

		virtual bool encode(std::ostream& os) const override;
		virtual bool decode(std::istream& is) override;
		virtual uint32_t neededSize(void) override;
		virtual bool firstPart(void) override;
		virtual bool lastPart(void) override;

	  private:
		ModbusStep modbusStep_ = ModbusStep::Step0;
		uint32_t neededSize_ = 2;

		std::vector<uint8_t> coils_;
	};

}

#endif
