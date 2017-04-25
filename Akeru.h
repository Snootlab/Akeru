/* Akeru.h - v4 [2016.07.29]
 * 
 * Copyleft Snootlab 2016 - inspired by TD1208 lib by IoTHerd (C) 2016
 *
 * Akeru is a library for Sigfox TD1208 use with the Arduino platform. 
 * The library is designed to use SoftwareSerial library for serial communication between TD1208 module and Arduino.
 * Current library coverage is:
 *	 - AT command 
 *	 - Sigfox payload transfer
 *	 - TD1208 temperature read
 *	 - TD1208 ID read
 *	 - TD1208 supply voltage read
 *	 - TD1208 hardware version read
 *	 - TD1208 firmware version read
 *	 - TD1208 power read
 *	 - TD1208 power set
 *   - TD1208 downlink request
 *   - Data conversion in hexadecimal
 */

#ifndef AKERU_H
#define AKERU_H

#if (ARDUINO >= 100)
	#include <Arduino.h>
#else
	#include <WProgram.h>
#endif

#include <SoftwareSerial.h>

#define ATOK "OK"
#define ATCOMMAND "AT"
#define ATID "ATI7"
#define ATHARDWARE "ATI11"
#define ATFIRMWARE "ATI13"
#define ATTEMPERATURE "ATI26"
#define ATVOLTAGE "ATI27"
#define ATKEEP "ATS300"
#define ATPOWER "ATS302"
#define ATDOWNLINK "AT$SB=1,2,1"
#define ATSIGFOXTX "AT$SS="
#define ATDISPLAY "AT&V"
#define DOWNLINKEND "+RX END"

#define ATCOMMAND_TIMEOUT (3000)
#define ATSIGFOXTX_TIMEOUT (30000)
#define ATDOWNLINK_TIMEOUT (45000)

// Set to 1 if you want to print the AT commands and answers
// on the serial monitor, set to 0 otherwise.
//#define _cmdEcho 1

class Akeru
{
	public:
		Akeru(unsigned int rx, unsigned int tx);
		void echoOn();
		void echoOff();
		bool begin();
		bool isReady();
		bool sendAT();
		bool sendPayload(const String payload);
		bool getTemperature(int *temperature);
		bool getID(String *id);
		bool getVoltage(float *voltage);
		bool getHardware(String *hardware);
		bool getFirmware(String *firmware);
		bool getPower(int *power);
		bool setPower(int power);
		bool receive(String *data);
		String toHex(int i);
		String toHex(unsigned int i);
		String toHex(long l);
		String toHex(unsigned long ul);
		String toHex(float f);
		String toHex(double d);
		String toHex(char c);
		String toHex(char *c, int length);
		String toHex(int8_t i);
		String toHex(uint8_t ui);

	private:
		bool sendATCommand(const String command, const int timeout, String *dataOut);
		SoftwareSerial* serialPort;
		unsigned long _lastSend;
		bool _cmdEcho = false;
};

#endif // AKERU_H
