#include <Akeru.h>
#include <SoftwareSerial.h>

int counter = 0;

void setup() 
{
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  Serial.println("Starting...");

  // Wait 1 second for the modem to warm up
  delay(1000);

  // Init modem
  Akeru.begin();
}

float getTemp(int pinValue) 
{
  // Convert 0 ~ 1024 to 0.0 ~ 5.0v
  float volts = pinValue * (5.0/1024.0);

  // TMP36 sends 10 mV/deg - 500 mV offset
  return (volts - 0.5) * 100;
}

// int is 16 bits, float is 32 bits. All little endian
typedef struct 
{
  int counter;
  int light;
  float temp;
} Payload;


void loop() 
{
  Payload p;

  p.counter = counter;
  p.light = analogRead(A1);
  p.temp = getTemp(analogRead(A2));

  Serial.print("Counter= "); Serial.println(p.counter);
  Serial.print("Light  = "); Serial.println(p.light);
  Serial.print("Temp   = "); Serial.println(p.temp);

  counter++;

  // Send in the mighty cloud!
  bool msgSent = Akeru.send(&p, sizeof(p));
  
  // Akeru.send() returns 0 if message failed. 
  // This is caused by either a network error
  // or the unavailability of the modem 
  // (call to isReady() prior to sending returned 0)
  if (!msgSent)
  {
    Serial.println("Modem not ready");
  }
  else 
  {
    Serial.println("Sent");
  }

  // Wait for 10 minutes.
  // Note that delay(600000) will block the Arduino (bug in delay()?)
  for (int second = 0; second < 600; second++) 
  {
    delay(1000);
  }
}