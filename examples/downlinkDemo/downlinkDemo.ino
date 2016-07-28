/* Akeru.h - downlinkDemo.ino
 * 
 * Copyleft Snootlab 2016
 * 
 * Downlink activation, and reception of a Sigfox network message
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

void setup() 
{
  Serial.begin(9600);
  
  // Check TD1208 communication
  if (!akeru.begin())
  {
    Serial.println("TD1208 KO");
    while(1);
  }
  
  //akeru.echoOn(); // uncomment this line to see AT commands
  
  String data = "";
  if (akeru.receive(&data))
  {
    Serial.print("Data received : 0x");
    Serial.println(data);
  }
}

void loop() 
{
}
