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

#ifndef __Modbus_ModbusReqReadDiscreteInputs_h__
#define __Modbus_ModbusReqReadDiscreteInputs_h__

#include <Modbus/Modbus/ModbusPackBase.h>

namespace Modbus
{

	class ModbusReqReadDiscreteInputs
	: public ModbusPackBase
	{
	  public:

		using SPtr = boost::shared_ptr<ModbusReqReadDiscreteInputs>;

		ModbusReqReadDiscreteInputs(void);
		virtual ~ModbusReqReadDiscreteInputs(void);

		void address(uint16_t address);
		uint16_t address(void);
		void numberInputs(uint16_t numberInputs);
		uint16_t numberInputs(void);

		virtual bool encode(std::ostream& os) const override;
		virtual bool decode(std::istream& is) override;
		virtual uint32_t neededSize(void) override;

	  private:
		uint32_t neededSize_ = 5;

		uint16_t address_ = 0;
		uint16_t numberInputs_ = 0;
	};

}

#endif