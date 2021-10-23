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
	ModbusRTU::sendReadCoilReq(ModbusTrx::SPtr& modbusTrx, uint8_t* req)
	{
		return true;
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

		return true;
	}

	bool
	ModbusRTU::close(void)
	{
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

}
