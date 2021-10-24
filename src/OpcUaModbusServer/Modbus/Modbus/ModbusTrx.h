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

namespace Modbus
{

	class ModbusTrx
	{
	  public:

		using SPtr = boost::shared_ptr<ModbusTrx>;

		ModbusTrx(void);
		virtual ~ModbusTrx(void);

		boost::asio::streambuf sbOut_;
	};

}

#endif
