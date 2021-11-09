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

#ifndef __Modbus_ModbusRTUServerTrx_h__
#define __Modbus_ModbusRTUServerTrx_h__

#include <functional>
#include <boost/shared_ptr.hpp>
#include "Modbus/Modbus/ModbusTypes.h"
#include "Modbus/ModbusRTU/ModbusRTUTrx.h"

namespace Modbus
{

	class ReadCoilRTUServerTrx
	: public ModbusRTUTrx
	{
      public:
		using SPtr = boost::shared_ptr<ReadCoilRTUServerTrx>;

		ReadCoilRTUServerTrx(void) : ModbusRTUTrx(ModbusFunction::ReadCoils) {}
		virtual ~ReadCoilRTUServerTrx(void) {}
	};

	class ReadDiscreteInputsRTUServerTrx
	: public ModbusRTUTrx
	{
      public:
		using SPtr = boost::shared_ptr<ReadDiscreteInputsRTUServerTrx>;

		ReadDiscreteInputsRTUServerTrx(void) : ModbusRTUTrx(ModbusFunction::ReadDiscreteInputs) {}
		virtual ~ReadDiscreteInputsRTUServerTrx(void) {}
	};

}

#endif
