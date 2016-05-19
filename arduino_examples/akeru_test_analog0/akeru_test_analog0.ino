#include <SoftwareSerial.h>
#include <Akeru.h>

// L LED is connected to pin 13, give it a name:
int led = 13;

// the setup routine runs once when you press reset:
void setup() 
{
  // initialize the digital pin of L led as an output
  pinMode(led, OUTPUT);  
  
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  Serial.println("Starting...");
  
  // Wait 1 second for the modem to warm
  delay(1000);
  
  // Init modem
  Akeru.begin();
}

void loop() 
{
  int sensorValue = analogRead(A0);
  
  // LED is on
  digitalWrite(led, HIGH);
  
  // Trace on serial console
  Serial.println(sensorValue);
  
  // Send in the mighty internet!
  bool msgSent = Akeru.send(&sensorValue,sizeof(sensorValue));
  
  // Akeru.send() returns 0 if message failed. 
  // This is caused by either a network error
  // or the unavailability of the modem 
  // (call to isReady() prior to sending returned 0)
  if (!msgSent)
  {
    Serial.println("Modem not ready");
  }
  
  // LED is off
  digitalWrite(led, LOW);
  
  // Wait for 10 minutes.
  // Note that delay(600000) will block the Arduino (bug in delay()?)
  for (int second = 0; second < 600; second++) 
  {
    delay(1000);
  }
}
