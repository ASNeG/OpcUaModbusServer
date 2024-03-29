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

#include "Modbus/Modbus/ModbusTrx.h"

namespace Modbus
{

	ModbusTrx::ModbusTrx(ModbusFunction modbusFunction)
	: modbusFunction_(modbusFunction)
	{
	}

	ModbusTrx::~ModbusTrx(void)
	{
	}

	ModbusFunction
	ModbusTrx::modbusFunction(void)
	{
		return modbusFunction_;
	}

	void
	ModbusTrx::req(const ModbusPackBase::SPtr& req)
	{
		req_ = req;
	}

	ModbusPackBase::SPtr&
	ModbusTrx::req(void)
	{
		return req_;
	}

	void
	ModbusTrx::res(const ModbusPackBase::SPtr& res)
	{
		res_ = res;
	}

	ModbusPackBase::SPtr&
	ModbusTrx::res(void)
	{
		return res_;
	}

	boost::asio::streambuf&
	ModbusTrx::sendBuffer(void)
	{
		return sendBuffer_;
	}

	boost::asio::streambuf&
	ModbusTrx::recvBuffer(void)
	{
		return recvBuffer_;
	}

}
