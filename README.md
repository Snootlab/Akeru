Akeru
=========

Requirements
------------

[Akeru](http://snootlab.com/lang-en/snootlab-shields/829-akeru-beta-33-en.html)
or
[Arduino/Genuino Uno](http://www.arduino.cc) and [Akene](http://snootlab.com/lang-en/snootlab-shields/889-akene-v1-en.html) or [TD1208 Breakout](http://snootlab.com/lang-en/snootlab-shields/962-breakout-td1208-connectivity-1-year-accessories-en.html)

Examples
--------

* akeru_test_3sensors : sending various values in a single message
* akeru_test_analog0 : sending values from a single analog sensor 

Installation
------------

Like any other library : http://arduino.cc/en/Hacking/Libraries

Use with an Akene or a TD1208 breakout
--------------------------------------

The library is configured for an Akeru.
In order to use it with an Akene or a TD1208 breakout, you'll need to modify the constructor in **Akeru.cpp** :

    _serial(5, 4)   // for Akeru
    _serial(4, 5)   // for Akene
	_serial(RX, TX) // for TD1208 breakout

Documentation
-------------

Visit our specific forum at http://forum.snootlab.com/viewforum.php?f=51