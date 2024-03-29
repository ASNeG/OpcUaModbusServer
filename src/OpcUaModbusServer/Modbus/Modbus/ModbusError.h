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

#ifndef __ModbusError_ModbusError_h__
#define __ModbusError_ModbusError_h__

#include <boost/system/error_code.hpp>
#include <string>
#include <iostream>
#include <sstream>

namespace Modbus
{

	enum class ModbusError : int
	{
		Success,
		SlaveInvalid,
		DecoderError,
		ChecksumError,
	};

	class ModbusErrorCategory
	: public boost::system::error_category
	{
	  public:

		ModbusErrorCategory(void);
		virtual ~ModbusErrorCategory(void);

		const char *name(void) const noexcept;
		std::string message(int ev) const;
	};

	#define MODBUS_ERROR(error_val, error_num) ModbusErrorCategory modbusError; \
											   boost::system::error_code error_val{(int)error_num, modbusError};

}

#endif
