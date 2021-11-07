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

#include <iostream>
#include "Modbus/ModbusRTU/ModbusRTUTrx.h"
#include "Modbus/ModbusRTU/ModbusRTUClient.h"
#include "Modbus/Modbus/ModbusReqReadCoil.h"
#include "Modbus/Modbus/ModbusResReadCoil.h"

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
		std::vector<bool> coilVec;

		// create read coil transaction
		auto modbusTrx = boost::make_shared<ReadCoilRTUClientTrx>();
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

		// create read coil respone
		auto res = boost::make_shared<ModbusResReadCoil>();
		modbusTrx->res(res);

		return sendRequest(modbusTrx);
	}

	void
	ModbusRTUClient::handleReadCoilRes(const boost::system::error_code& ec, const ModbusRTUTrx::SPtr& modbusRTUTrx)
	{
		std::vector<bool> coilVec;

		auto modbusTrx = reinterpret_cast<const ReadCoilRTUClientTrx::SPtr&>(modbusRTUTrx);
		if (ec) {
			modbusTrx->readCoilResFunc_(ec, coilVec);
			return;
		}

		// check response
		auto req = reinterpret_cast<const ModbusReqReadCoil::SPtr&>(modbusTrx->req());
		auto res = reinterpret_cast<const ModbusResReadCoil::SPtr&>(modbusTrx->res());

		// get coils from response
		uint16_t numCoils = req->numberCoils();
		for (uint32_t idx = 0; idx < res->coils().size(); idx++) {
			uint8_t byte = res->coils()[idx];
			int8_t byteIndex = 7;
			while (byteIndex >= 0 && numCoils > 0) {

				if ((byte & (0x01 << byteIndex)) > 0) {
					coilVec.push_back(true);
				}
				else {
					coilVec.push_back(false);
				}

				numCoils--;
				byteIndex--;
			}
		}

		// call coil response function
		modbusTrx->readCoilResFunc_(ec, coilVec);
	}

}