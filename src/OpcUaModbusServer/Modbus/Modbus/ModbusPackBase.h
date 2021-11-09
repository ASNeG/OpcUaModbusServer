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

#ifndef __Modbus_ModbusPackBase_h__
#define __Modbus_ModbusPackBase_h__

#include <boost/shared_ptr.hpp>
#include <boost/system/error_code.hpp>
#include "Modbus/Modbus/ModbusTypes.h"
#include "Modbus/Modbus/ModbusException.h"

namespace Modbus
{

	enum class ModbusPackState
	{
		Header,
		Meta,
		Data,
		Tail
	};

	class ModbusPackBase
	{
	  public:

		using SPtr = boost::shared_ptr<ModbusPackBase>;

		ModbusPackBase(ModbusFunction modbusFunction);
		virtual ~ModbusPackBase(void);

		uint8_t modbusFunction(void) const;
		boost::system::error_code ec(void);
		void ec(ModbusException ec);

		virtual bool encode(std::ostream& os) const = 0;
		virtual bool decode(std::istream& is) = 0;
		uint32_t neededSize(void);
		bool firstPart(void);
		bool lastPart(void);

		bool decodeEC(std::istream& is);
		bool encodeEC(std::ostream& os);

	  protected:
		uint32_t neededSize_ = 1;
		ModbusPackState modbusPackState_ = ModbusPackState::Header;
		boost::system::error_code ec_;

	  private:
		ModbusFunction modbusFunction_;
	};

}

#endif
