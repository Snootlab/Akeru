Akeru - TD1208 library for Arduino
=========

Requirements
------------

[Akeru](http://snootlab.com/lang-en/snootlab-shields/829-akeru-beta-33-en.html)
or
[Arduino/Genuino Uno](http://snootlab.com/lang-en/arduino-genuino-en/956-genuino-uno-arduino-uno-en.html) + [Akene](http://snootlab.com/lang-en/snootlab-shields/889-akene-v1-en.html) or [TD1208 Breakout](http://snootlab.com/lang-en/snootlab-shields/962-breakout-td1208-connectivity-1-year-accessories-en.html)

Examples
--------

* demoTest : full demo sketch
  * Checks if the modem is available
  * reads temperature, supply voltage, hardware & firmware version, power level
  * sends temperature & supply voltage on Sigfox network
* downlinkDemo : how to receive data from the Sigfox network
* sendMultipleValues : sending various values in a single message
* sendSingleValues  : sending values from a single analog sensor 

Installation
------------

Like any other library : http://arduino.cc/en/Hacking/Libraries

Use
--------------------------------------

####Sigfox module initialization

Starting with version 4 of the library, RX/TX definition is directly in the sketch. There's a single library file to include and a simple line of code to map the signals according to your device :

```
#include <Akeru.h>

/*   Snootlab device | TX | RX
               Akeru | D4 | D5
               Akene | D5 | D4
            Breakout | your pick */
#define TX 4
#define RX 5

Akeru akeru(RX, TX);
```

####Powering up

A single line to add in your `void setup()` :

```
akeru.begin(); // returns 1 when everything went ok
```

####Sending data

Data is sent to the Sigfox network in hexadecimal format, and the payload has to be a String of all elements you want to send. To ensure proper conversion of your variables, you can use `akeru.toHex()` method :

```
int val = analogRead(0);
String valString = akeru.toHex(val);
akeru.sendPayload(varString);
```

Documentation
-------------

Visit our specific forum at http://forum.snootlab.com/viewforum.php?f=51

