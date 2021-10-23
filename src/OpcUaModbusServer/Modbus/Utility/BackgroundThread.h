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

#ifndef __Modbus_BackgroundThread_h__
#define __Modbus_BackgroundThread_h__

#define BOOST_THREAD_PROVIDES_FUTURE
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/thread/future.hpp>

namespace Modbus
{

	class BackgroundThread
	{
	  public:
		BackgroundThread(void);
		~BackgroundThread(void);

		void startup(void);
		void shutdown(void);

		boost::asio::io_context::strand* strand(void);
		boost::asio::io_context& io_context(void);

	  private:
		boost::thread* thread_ = nullptr;
		boost::asio::io_context io_context_;
		boost::asio::io_context::work* work_ = nullptr;
		boost::asio::io_context::strand* strand_ = nullptr;

		boost::promise<void> startSync_;
		boost::promise<void> stopSync_;

		void threadLoop(void);
	};

}

#endif
