#include "Arduino.h"
#include "flasher.h"

Flasher led1(15, 200, 300);

void setup()
{

}

void loop()
{
  led1.Update();
}
