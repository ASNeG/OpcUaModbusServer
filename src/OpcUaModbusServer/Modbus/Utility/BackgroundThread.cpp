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
#include "Modbus/Utility/BackgroundThread.h"

namespace Modbus
{

	BackgroundThread::BackgroundThread(void)
	{
	}

	BackgroundThread::~BackgroundThread(void)
	{
	}

	void
	BackgroundThread::startup(void)
	{
		// start synchronization
		auto f = startSync_.get_future();

		// start background thread
		work_ = new boost::asio::io_context::work(io_context_);
		thread_ = new boost::thread(
			[this](void) {
				threadLoop();
			}
		);

		// wait until the thread has started
		f.get();

		// create strand
		strand_ = new boost::asio::io_context::strand(io_context_);
	}

	void
	BackgroundThread::shutdown(void)
	{
		// stop synchronization
		auto f = stopSync_.get_future();

		// stop background thread
		if (work_) {
			delete work_;
			work_ = nullptr;
		}

		// stop service
		io_context_.stop();

		// wait until the thread has stopped
		f.get();

		// delete thread
		if (thread_) {
			delete thread_;
			thread_ = nullptr;
		}

		// delete strand
		if (strand_) {
			delete strand_;
			strand_ = nullptr;
		}
	}

	void
	BackgroundThread::threadLoop(void)
	{
		// synchronization starting thread
		startSync_.set_value();

		// run new thread
		io_context_.run();

		// synchronization stopping thread
		stopSync_.set_value();
	}

	boost::asio::io_context::strand*
	BackgroundThread::strand(void)
	{
		return strand_;
	}

	boost::asio::io_context&
	BackgroundThread::io_context(void)
	{
		return io_context_;
	}

}
