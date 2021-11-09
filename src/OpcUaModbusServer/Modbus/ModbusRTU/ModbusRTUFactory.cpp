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

#include <boost/make_shared.hpp>
#include "Modbus/Modbus/ModbusReqReadCoil.h"
#include "Modbus/Modbus/ModbusResReadCoil.h"
#include "Modbus/Modbus/ModbusReqReadDiscreteInputs.h"
#include "Modbus/Modbus/ModbusResReadDiscreteInputs.h"
#include "Modbus/ModbusRTU/ModbusRTUServerTrx.h"
#include "Modbus/ModbusRTU/ModbusRTUFactory.h"

namespace Modbus
{

	ModbusRTUFactory::ModbusRTUFactory(void)
	{
	}

	ModbusRTUFactory::~ModbusRTUFactory(void)
	{
	}

	ModbusRTUTrx::SPtr
	ModbusRTUFactory::createModbusRTUTrx(uint8_t function)
	{
		ModbusRTUTrx::SPtr modbusRTUTrx;

		switch ((ModbusFunction)function)
		{
			case ModbusFunction::None:
			{
				modbusRTUTrx = boost::make_shared<ModbusRTUTrx>();
				break;
			}
			case ModbusFunction::ReadCoils:
			{
				modbusRTUTrx = boost::make_shared<ReadCoilRTUServerTrx>();
				modbusRTUTrx->req(boost::make_shared<ModbusReqReadCoil>());
				modbusRTUTrx->res(boost::make_shared<ModbusResReadCoil>());
				break;
			}
			case ModbusFunction::ReadDiscreteInputs:
			{
				modbusRTUTrx = boost::make_shared<ReadDiscreteInputsRTUServerTrx>();
				modbusRTUTrx->req(boost::make_shared<ModbusReqReadDiscreteInputs>());
				modbusRTUTrx->res(boost::make_shared<ModbusResReadDiscreteInputs>());
				break;
			}
			default:
			{
				// do nothing
			}
		}

		return modbusRTUTrx;
	}

}
