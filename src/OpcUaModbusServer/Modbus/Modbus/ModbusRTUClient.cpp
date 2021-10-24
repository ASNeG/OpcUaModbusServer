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

#include "Modbus/Modbus/ModbusRTUClient.h"

namespace Modbus
{

	class ReadCoilTrx
	: public ModbusTrx
	{
	  public:
		using SPtr = boost::shared_ptr<ReadCoilTrx>;

		ModbusRTUClient::ReadCoilResFunc readCoilResFunc_ = nullptr;
	};

	ModbusRTUClient::ModbusRTUClient(void)
	: ModbusRTU()
	{
	}

	ModbusRTUClient::~ModbusRTUClient(void)
	{
	}

	bool
	ModbusRTUClient::readCoil(
		ReadCoilResFunc readCoilResFunc,
		uint8_t slave,
		uint16_t address,
		uint16_t numberCoils
	)
	{
		// create read coil request transaction
		auto trx = boost::make_shared<ReadCoilTrx>();
		trx->readCoilResFunc_ = readCoilResFunc;

		// send function
		SendFunc sendReqFunc = {
			[this, trx](uint8_t reqLen, uint8_t* reqBuf) {
				ModbusTrx::SPtr modbusTrx = trx;
				return sendRequest(modbusTrx, reqLen, reqBuf);
			}
		};

		// send read coil request
		return sendReadCoilReq(sendReqFunc, slave, address, numberCoils);
	}

}
