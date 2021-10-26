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

#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include "Modbus/Utility/Log.h"
#include "Modbus/Modbus/ModbusRTU.h"
#include "Modbus/Modbus/ModbusError.h"

namespace Modbus
{

	ModbusRTU::ModbusRTU(void)
	: Modbus()
	{
	}

	ModbusRTU::~ModbusRTU(void)
	{
	}

	bool
	ModbusRTU::open(
		const std::string& device,
		uint32_t baud,
		char parity,
		uint8_t dataBits,
		uint8_t stopBits
	)
	{
		device_ = device;

		// check baud rate
		Speed speed;
		switch (baud)
		{
			case 50: { speed = B50; break; }
			case 75: { speed = B75; break; }
			case 110: { speed = B110; break; }
			case 134: { speed = B134; break; }
			case 150: { speed = B150; break; }
			case 200: { speed = B200; break; }
			case 300: { speed = B300; break; }
			case 600: { speed = B600; break; }
			case 1200: { speed = B1200; break; }
			case 1800: { speed = B1800; break; }
			case 2400: { speed = B2400; break; }
			case 4800: { speed = B4800; break; }
			case 9600: { speed = B9600; break; }
			case 19200: { speed = B19200; break; }
			case 38400: { speed = B38400; break; }
			default:
			{
				Log(LogLevel::Error, "can not open device because baud parameter invalid")
					.parameter("Device", device)
					.parameter("Baud", baud);
				return false;
			}
		}

		// check parity
		if (parity != 'N' && parity != 'O' && parity != 'E') {
			Log(LogLevel::Error, "can not open device because parity parameter invalid")
				.parameter("Device", device)
				.parameter("Parity", parity);
			return false;
		}

		// check data bits
		tcflag_t dataBitsFlag;
		switch (dataBits)
		{
			case 5: dataBitsFlag = CS5; break;
			case 6: dataBitsFlag = CS6; break;
			case 7: dataBitsFlag = CS7; break;
			case 8: dataBitsFlag = CS8; break;
			default:
			{
				Log(LogLevel::Error, "can not open device because data bit parameter invalid")
					.parameter("Device", device)
					.parameter("DataBits", (uint32_t)dataBits);
				return false;
			}
		}

		// check stop bits
		if (stopBits != 1 && stopBits != 2) {
			Log(LogLevel::Error, "can not open device because stop bit parameter invalid")
				.parameter("Device", device)
				.parameter("StopBits", (uint32_t)stopBits);
			return false;
		}

		// open terminal device
		int flags = O_RDWR | O_NOCTTY | O_NDELAY | O_EXCL;
		fd_ = ::open(device.c_str(), flags);
		if (fd_ == -1) {
			Log(LogLevel::Error, "open device error")
				.parameter("Device", device)
				.parameter("Error", strerror(errno));
			return false;
		}

		// save old terminal attributes
		if (tcgetattr(fd_, &oldTermios_) == -1) {
			Log(LogLevel::Error, "can not open device because get terminal attributes error")
				.parameter("Device", device)
				.parameter("Error", strerror(errno));
			return false;
		}

		// set input speed and output speed
		TermIOS termios;
		if (cfsetispeed(&termios, speed) == -1) {
			Log(LogLevel::Error, "can not open device because set output speed error")
				.parameter("Device", device);
			return false;
		}
		if (cfsetospeed(&termios, speed) == -1) {
			Log(LogLevel::Error, "can not open device because set output speed error")
				.parameter("Device", device);
			return false;
		}

		//
		// set control modes
		//

		// Enable receiver
		termios.c_cflag |= CREAD;

		// Ignore modem control lines
		termios.c_cflag |= CLOCAL;

		// number of data bits
		termios.c_cflag &= ~CSIZE;
		termios.c_cflag |= dataBitsFlag;

		// number of stop bits
	    if (stopBits == 1) {
	    	termios.c_cflag &=~ CSTOPB;
	    }
	    else {
	    	termios.c_cflag |= CSTOPB;
	    }

	    // parity
	    if (parity == 'N') { // None
	        termios.c_cflag &=~ PARENB;
	    }
	    else if (parity == 'E') { // Even
	        termios.c_cflag |= PARENB;
	        termios.c_cflag &=~ PARODD;
	    }
	    else { // Odd
	        termios.c_cflag |= PARENB;
	        termios.c_cflag |= PARODD;
	    }

	    //
	    // set local modes
	    //

	    // ICANON Enable canonical mode
	    // ECHO   Echo input characters
	    // ECHOE  If ICANON is also set, the ERASE character erases the preceding
	    //        input character, and WERASE erases the preceding word
	    // ISIG   When any of the characters INTR, QUIT, SUSP, or DSUSP are
        //        received, generate the corresponding signal
	    termios.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

	    //
	    // set input modes
	    //

	    // Enable input parity checking
	    // IXON   Enable XON/XOFF flow control on output
	    // IXOFF  Enable XON/XOFF flow control on input
	    // IXANY  (XSI) Typing any character will restart stopped output.
        //        (The default is to allow just the START character to
        //        restart output.)
	    if (parity == 'N') { // None
	        termios.c_iflag &= ~INPCK;
	    }
	    else {
	        termios.c_iflag |= INPCK;
	    }
	    termios.c_iflag &= ~(IXON | IXOFF | IXANY);

	    //
	    // set output modes
	    //

	    // OPOST  Enable implementation-defined output processing
	    termios.c_oflag &=~ OPOST;

	    //
	    // set specialö characters
	    //

	    // Minimum number of characters for noncanonical read (MIN)
	    termios.c_cc[VMIN] = 0;

	    // Timeout in deciseconds for noncanonical read (TIME)
	    termios.c_cc[VTIME] = 0;

	    // save new terminal attributes
	    if (tcsetattr(fd_, TCSANOW, &termios) < 0) {
			Log(LogLevel::Error, "can not open device because set terminal attributes error")
				.parameter("Device", device)
				.parameter("Error", strerror(errno));
			return false;
	    }

	    // startup background thread
	    backgroundThread_.startup();

	    // create input stream and output stream
	    in_ = new boost::asio::posix::stream_descriptor(backgroundThread_.io_context());
	    in_->assign(fd_);
	    out_ = new boost::asio::posix::stream_descriptor(backgroundThread_.io_context());
	    out_->assign(fd_);

		return true;
	}

	bool
	ModbusRTU::close(void)
	{
		// shutdown background thread
		backgroundThread_.shutdown();

		// delete input and output stream descriptor
		if (in_) {
			delete in_;
			in_ = nullptr;
		}
		if (out_) {
			delete out_;
			out_ = nullptr;
		}

		// check file descriptor
		if (fd_ == -1) {
			return true;
		}

		// set old terminal attributes
	    tcsetattr(fd_, TCSANOW, &oldTermios_);

		// close terminal device
	    ::close(fd_);
	    fd_ = -1;
	    return true;
	}

	bool
	ModbusRTU::sendRequest(const ModbusRTUTrx::SPtr& modbusTrx)
	{
		// check modbus trx
#if 0
		if (sendRequestRunning_) {
			Log(LogLevel::Error, "can not send request because sender busy")
				.parameter("Device", device_);
			return false;
		}
#endif

		// encode slave
		boost::asio::streambuf sbHeader;
		std::iostream iosHeader(&sbHeader);
		uint8_t slave = modbusTrx->slave();
		iosHeader.write((char*)&slave, 1);

		// encode request
		boost::asio::streambuf sbReq;
		std::iostream iosReq(&sbReq);
		if (!modbusTrx->req()->encode(iosReq)) {
			Log(LogLevel::Error, "can not send request because request encoder error")
				.parameter("Device", device_)
				.parameter("ModbusFunction", (uint32_t)modbusTrx->req()->modbusFunction());
			return false;
		}

		// add crc 16 checksum
		crc16_.reset();
		crc16_.process(sbReq, sbReq.size());
		uint16_t checksum = crc16_.checksum();

		boost::asio::streambuf sbCRC;
		std::iostream iosCRC(&sbCRC);
		uint8_t crc[2] = { (uint8_t)((checksum & 0xFF00) >> 8), (uint8_t)(checksum & 0x00FF) };
		iosCRC.write((char*)crc, 2);

		// add data to send stream buffer
		std::iostream ios(&modbusTrx->sendBuffer());
		ios << iosHeader.rdbuf();
		ios << iosReq.rdbuf();
		ios << iosCRC.rdbuf();

		// we send in the background thread
		backgroundThread_.strand()->dispatch(
			[this, modbusTrx](void) {
				sendRequestStrand(modbusTrx);
			}
		);

		return true;
	}

	void
	ModbusRTU::sendRequestStrand(const ModbusRTUTrx::SPtr& modbusTrx)
	{
		assert(!backgroundThread_.strand()->running_in_this_thread());

		// send request to slave
		boost::asio::async_write(
			*out_,
			modbusTrx->sendBuffer(),
			backgroundThread_.strand()->wrap(
				[this, modbusTrx](const boost::system::error_code& ec, size_t bt) {
					sendRequestCompleteStrand(modbusTrx, ec, bt);
		    	}
			)
	    );
	}

	void
	ModbusRTU::sendRequestCompleteStrand(const ModbusRTUTrx::SPtr& modbusTrx, const boost::system::error_code& ec, size_t bt)
	{
		// check error code
		if (ec) {
			Log(LogLevel::Error, "send request error")
				.parameter("Device", device_)
				.parameter("ErrorMessage", ec.message());
			modbusTrx->handleEvent(ec, modbusTrx);
			return;
		}

		// receive response from slave
		recvResponseStrand(modbusTrx);
	}

	void
	ModbusRTU::recvResponseStrand(
		const ModbusRTUTrx::SPtr& modbusTrx
	)
	{
		// receive some bytes from slave
		uint32_t size = modbusTrx->res()->neededSize();

		if (modbusTrx->res()->firstPart()) size = size + 1;	// read slave
		if (modbusTrx->res()->lastPart()) size = size + 2; // read crc

		boost::asio::async_read(
			*out_,
			modbusTrx->recvBuffer(),
			boost::asio::transfer_exactly(size),
			backgroundThread_.strand()->wrap(
				[this, modbusTrx](const boost::system::error_code& ec, std::size_t bt) {
					recvResponseCompleteStrand(modbusTrx, ec, bt);
				}
			)
		);
	}

	void
	ModbusRTU::recvResponseCompleteStrand(
		const ModbusRTUTrx::SPtr& modbusTrx,
		const boost::system::error_code& ec,
		size_t bt
	)
	{
		uint8_t b[2];

		bool firstPart = modbusTrx->res()->firstPart();
		bool lastPart = modbusTrx->res()->lastPart();

		// check error code
		if (ec) {
			Log(LogLevel::Error, "recv response error")
				.parameter("Device", device_)
				.parameter("ErrorMessage", ec.message());
			modbusTrx->handleEvent(ec, modbusTrx);
			return;
		}

		std::iostream ios(&modbusTrx->recvBuffer());

		// decode and check slave
		if (firstPart) {
			ios.read((char*)b, 1);

			if (b[0] != modbusTrx->slave()) {
				MODBUS_ERROR(ec, ModbusError::SlaveInvalid)
				Log(LogLevel::Error, "recv response error")
					.parameter("Device", device_)
					.parameter("ErrorMessage", ec.message());
				modbusTrx->handleEvent(ec, modbusTrx);
				return;
			}
		}

		// calculate CRC
		uint32_t size = modbusTrx->recvBuffer().size();
		if (lastPart) size -= 2;
		crc16_.reset();
		crc16_.process(modbusTrx->recvBuffer(), size);

		// decode response
		if (!modbusTrx->res()->decode(ios)) {
			MODBUS_ERROR(ec, ModbusError::DecoderError)
			Log(LogLevel::Error, "receive response error because response decoder error")
				.parameter("Device", device_)
				.parameter("ModbusFunction", (uint32_t)modbusTrx->req()->modbusFunction());
			modbusTrx->handleEvent(ec, modbusTrx);
			return;
		}

		// decode and check crc
		if (lastPart) {
			// decode crc
			ios.read((char*)b, 2);

			// check crc
			uint16_t checksum = (b[0] << 8) + b[1];
			if (!crc16_.validateChecksum(checksum)) {
				MODBUS_ERROR(ec, ModbusError::ChecksumError)
				Log(LogLevel::Error, "receive response error because received checksum error")
					.parameter("Device", device_)
					.parameter("ModbusFunction", (uint32_t)modbusTrx->req()->modbusFunction());
				modbusTrx->handleEvent(ec, modbusTrx);
				return;
			}

			MODBUS_ERROR(ec, ModbusError::Success)
			modbusTrx->handleEvent(ec, modbusTrx);
		}
	};

}
