/*
  flasher.h - Header file for flashing leds
*/

#ifndef flasher_h
#define flasher_h

#include "Arduino.h"

class Flasher
{
  int ledPin;
  unsigned long OnTime;
  unsigned long OffTime;
  int ledState;
  unsigned long previousMillis;

public:
  Flasher(int pin, long on, long off)
  {
    ledPin = pin;
    pinMode(ledPin, OUTPUT);

    OnTime = on;
    OffTime = off;

    ledState = LOW;
    previousMillis = 0;
  }

  void Update()
  {
    unsigned long currentMillis = millis();

    if((ledState == HIGH) && (currentMillis >= OnTime))
    {
      ledState = LOW;
      previousMillis = currentMillis;
      digitalWrite(ledPin, ledState);
    }
    if((ledState == LOW) && (currentMillis - previousMillis >= OffTime))
    {
      ledState = HIGH;
      previousMillis = currentMillis;
      digitalWrite(ledPin, ledState);
    }
  }
};

#endif
