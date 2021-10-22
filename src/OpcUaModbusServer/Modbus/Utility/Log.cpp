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
#include "boost/date_time/posix_time/posix_time.hpp"
#include "Modbus/Utility/Log.h"

namespace Modbus
{

	Log::LogFunc logFunc_ = nullptr;

	Log::Log(LogLevel logLevel, const std::string& message)
	{
		logLevel_ = logLevel;
		message_ = message;
	}

	Log::~Log(void)
	{
		if (logFunc_) {
			logFunc_(logLevel_, message_, parameter_);
		}
		else {
			auto now = boost::posix_time::microsec_clock::local_time();
			std::cout << now << " " << logLevel() << " " << message_;
			if  (parameter_ != "") {
				std::cout << ": " << parameter_;
			}
			std::cout << std::endl;
		}
	}

	void
	Log::addParameter(const std::string& parameter, const std::string value)
	{
		if (parameter_ != "") {
			parameter_.append(", ");
		}
		parameter_.append(parameter);
		parameter_.append("=<");
		parameter_.append(value);
		parameter_.append(">");
	}

	void
	Log::logFunc(LogFunc logFunc)
	{
		logFunc_ = logFunc;
	}

	std::string
	Log::logLevel(void)
	{
		switch (logLevel_)
		{
			case LogLevel::Error:		return "ERR";
			case LogLevel::Warning:		return "WRN";
			case LogLevel::Info:		return "INF";
			case LogLevel::Debug:		return "DBG";
			case LogLevel::Trace:		return "TRC";
			default:					return "UKN";
		}
		return "";
	}

}
