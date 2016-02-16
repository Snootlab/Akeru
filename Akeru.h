// Akeru library - http://akeru.cc
//
// copyleft Snootlab, 2016
// this code is public domain, enjoy!

#ifndef AKERU_H
#define AKERU_H

#if (ARDUINO >= 100)
	#include <Arduino.h>
#else
	#include <WProgram.h>
#endif

#include <SoftwareSerial.h>

class Akeru_ {
    public:
        Akeru_();
        ~Akeru_();
        void begin();
		void listen();
        bool isReady();
        bool send(const void* data, uint8_t len);
        uint8_t getRev();
        unsigned long getID();
        bool setPower(uint8_t power);

        enum RETURN_CODE {
            OK = 'O',
            KO = 'K',
            SENT = 'S'
        };

    private:
        SoftwareSerial _serial;
        unsigned long _lastSend;

        uint8_t _nextReturn();
};

extern Akeru_ Akeru;

#endif