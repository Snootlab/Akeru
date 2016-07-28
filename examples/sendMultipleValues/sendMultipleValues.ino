/* Akeru.h - sendMultipleValues.ino
 * 
 * Copyleft Snootlab 2016
 * 
 * How to send 3 variables in a row on the Sigfox network :
 *  - counter : how many loops we've done (int)
 *  - light : analog value from a LDR on A1 (int)
 *  - temperature : analog value from a LM35DZ on A2 (float)
 * 
 * Note that Sigfox messages are 12 bytes long max
 * So here with two ints (2*2 bytes) + one float (4 bytes)
 * we still have 4 bytes available for other data
 */

#include <Akeru.h>

// TD1208 Sigfox module IO definition
/*   Snootlab device | TX | RX
               Akeru | D4 | D5
               Akene | D5 | D4
            Breakout | your pick */
#define TX 4
#define RX 5

// Sigfox instance management 
Akeru akeru(RX, TX);

unsigned int counter = 0;

void setup() 
{
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  Serial.println("Starting...");

  // Check TD1208 communication
  if (!akeru.begin())
  {
    Serial.println("TD1208 KO");
    while(1);
  }
  
  //akeru.echoOn(); // uncomment this line to see AT commands
}

float getTemp(int pinValue) 
{
  // Convert [0...1024] to [0.0...5.0v]
  float volts = pinValue * (5.0/1024.0);
  // LM35DZ sends 10 mV/deg
  return volts * 100.0;
}

void loop() 
{
  int light = analogRead(A1);
  float temp = getTemp(analogRead(A2));

  Serial.print("Counter = "); Serial.println(counter);
  Serial.print("Light   = "); Serial.println(light);
  Serial.print("Temp    = "); Serial.println(temp);

  // Convert to hexadecimal before sending
  String c = akeru.toHex(counter);
  String l = akeru.toHex(light);
  String t = akeru.toHex(temp);

  String msg = c + l + t; // Put everything together

  // Send in the mighty cloud!
  // akeru.send() returns 0 if message failed. 
  if (akeru.sendPayload(msg))
  {
    Serial.println("Message sent !");
  }

  counter++;
  
  // Wait for 10 minutes.
  // Note that delay(600000) will block the Arduino (bug in delay()?)
  for (int second = 0; second < 600; second++) 
  {
    delay(1000);
  }
}
