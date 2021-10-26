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

#ifndef __Modbus_ModbusTrx_h__
#define __Modbus_ModbusTrx_h__

#include "boost/shared_ptr.hpp"
#include "boost/asio.hpp"
#include "Modbus/Modbus/ModbusTypes.h"
#include "Modbus/Modbus/ModbusPackBase.h"

namespace Modbus
{

	class ModbusTrx
	{
	  public:

		using SPtr = boost::shared_ptr<ModbusTrx>;

		ModbusTrx(ModbusFunction modbusFunction);
		virtual ~ModbusTrx(void);

		ModbusFunction modbusFunction(void);
		void req(const ModbusPackBase::SPtr& req);
		ModbusPackBase::SPtr& req(void);
		void res(ModbusPackBase::SPtr& res);
		ModbusPackBase::SPtr& res(void);

		boost::asio::streambuf& sendBuffer(void);
		boost::asio::streambuf& recvBuffer(void);

	  private:
		ModbusFunction modbusFunction_;			// modbus function
		ModbusPackBase::SPtr req_ = nullptr;	// modbus request
		ModbusPackBase::SPtr res_ = nullptr;	// modbus response

		boost::asio::streambuf sendBuffer_;		// send stream buffer
		boost::asio::streambuf recvBuffer_;		// receive stream buffer
	};

}

#endif
