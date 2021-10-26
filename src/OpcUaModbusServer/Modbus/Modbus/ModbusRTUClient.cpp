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

#include "Modbus/Modbus/ModbusRTUTrx.h"
#include "Modbus/Modbus/ModbusRTUClient.h"
#include "Modbus/Modbus/ModbusReqReadCoil.h"

namespace Modbus
{

	ModbusRTUClient::ModbusRTUClient(void)
	: ModbusRTU()
	{
	}

	ModbusRTUClient::~ModbusRTUClient(void)
	{
	}

	bool
	ModbusRTUClient::readCoilReq(
		ReadCoilResFunc readCoilResFunc,
		uint8_t slave,
		uint16_t address,
		uint16_t numberCoils
	)
	{
		// create read coil transaction
		auto modbusTrx = boost::make_shared<ReadCoilTrx>();
		modbusTrx->slave(slave);
		modbusTrx->readCoilResFunc_ = readCoilResFunc;
		modbusTrx->handleResFunc_ = [this](const boost::system::error_code& ec, const ModbusRTUTrx::SPtr& modbusTrx) {
			handleReadCoilRes(ec, modbusTrx);
		};

		// create read coil request
		auto req = boost::make_shared<ModbusReqReadCoil>();
		req->address(address);
		req->numberCoils(numberCoils);
		modbusTrx->req(req);

		return sendRequest(modbusTrx, slave);
	}

	void
	ModbusRTUClient::handleReadCoilRes(const boost::system::error_code& ec, const ModbusRTUTrx::SPtr& modbusTrx)
	{
		// FIXME: todo
	}

}
