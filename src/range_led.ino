//#include <avr/power.h>
#include "RunningMedian.h"
#include "Adafruit_NeoPixel.h"

#define LEDPIN 2
#define TRIGPIN 5
#define ECHOPIN 6

RunningMedian samples = RunningMedian(21);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, LEDPIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(TRIGPIN,OUTPUT);
  pinMode(ECHOPIN,INPUT);

  strip.begin();
  strip.setBrightness(10);
  strip.show();
}

void loop() {
  long dur, limit;
  int x;
  dur = sonicMedian();

  Serial.println(dur);

  //red step - 1
  if (dur > 0 && dur < 2601)
  {
    limit = dur/188;
    for (x=0; x<=limit; x++) {
      strip.setPixelColor(x, strip.Color(255, 0, 0));
    }
    for (x=limit+1; x<=15; x++) {
      strip.setPixelColor(x, strip.Color(0, 255, 0));
    }
  }

  //green step - 2
  if (dur > 2600 && dur < 5201)
  {
    limit = (dur-2600)/188;
    if (limit == 0) limit = 1;
    for (x=0; x<=limit; x++) {
      strip.setPixelColor(x, strip.Color(0, 255, 0));
    }
    for (x=limit+1; x<=15; x++) {
      strip.setPixelColor(x, strip.Color(0, 0, 255));
    }
  }

  //blue step - 3
  if (dur > 5200 && dur < 7801)
  {
    limit = (dur-5200)/188;
    if (limit == 0) limit = 1;
    for (x=0; x<=limit; x++) {
      strip.setPixelColor(x, strip.Color(0, 0, 255));
    }
    for (x=limit+1; x<=15; x++) {
      strip.setPixelColor(x, strip.Color(255, 0, 0));
    }
  }

    //other step - 4
  if (dur > 7800 && dur < 10401)
  {
    limit = (dur-7800)/188;
    if (limit == 0) limit = 1;
    for (x=0; x<=limit; x++) {
      strip.setPixelColor(x, strip.Color(255, 0, 0));
    }
    for (x=limit+1; x<=15; x++) {
      strip.setPixelColor(x, strip.Color(75, 125, 25));
    }
  }
  strip.show();
  delay(30);
}

long sonicMedian() {
  long x = RangeRead();

  samples.add(x);
  long m = samples.getAverage(10);

  //Serial.println(m);
  return m;
  delay(15);
}

long RangeRead() {
  long dur;

  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);
  dur = pulseIn(ECHOPIN, HIGH);
  return dur;
}
