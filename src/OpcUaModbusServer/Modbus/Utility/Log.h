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

#ifndef __Modbus_Log_h__
#define __Modbus_Log_h__

#include <string>
#include <sstream>
#include <functional>
#include <iomanip>
#include <boost/asio/streambuf.hpp>

namespace Modbus
{

	enum class LogLevel {
		Error,
		Warning,
		Info,
		Debug,
		Trace
	};

	class Log
	{
	  public:

		using LogFunc = std::function<void (LogLevel, const std::string&, const std::string&)>;

		Log(LogLevel logLevel, const std::string& message);
		~Log(void);

		template<typename T>
		  Log& parameter(
		     const std::string& parameterName,
			 const T& parameterValue
		  ) {
			  std::stringstream ss;
			  ss << parameterValue;
			  addParameter(parameterName, ss.str());
			  return *this;
		  }

		Log& parameter(
	        const std::string& parameterName,
			const boost::asio::streambuf& streambuf
		)
		{
			std::stringstream ss;

			uint32_t size = streambuf.size();
			std::vector<char> target(size);
			buffer_copy(boost::asio::buffer(target), streambuf.data());

			for (uint32_t idx = 0; idx < size; idx++) {
				if (idx != 0) ss << " ";
				ss << std::setw(2) << std::setfill('0') << std::hex << (uint32_t)target[idx];
			}

			addParameter(parameterName, ss.str());
			return *this;
		}

		static void logFunc(LogFunc logFunc);

	  private:
		static LogFunc logFunc_;

		LogLevel logLevel_;
		std::string message_;
		std::string parameter_;

		void addParameter(const std::string& parameter, const std::string value);
		std::string logLevel(void);
	};

}

#endif
