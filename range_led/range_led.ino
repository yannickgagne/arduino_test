#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define LEDPIN 8
#define TRIGPIN 6
#define ECHOPIN 7

Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, LEDPIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(TRIGPIN,OUTPUT);
  pinMode(ECHOPIN,INPUT);
  
  strip.begin();
  strip.setBrightness(15);
  strip.show();
}

void loop() {
  // put your main code here, to run repeatedly:
  long dur, distCm, distIn;
  int num, limit, x;
  
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(15);
  digitalWrite(TRIGPIN, LOW);
  dur = pulseIn(ECHOPIN, HIGH);

  //red step - 1
  if (dur > 0 && dur < 3001)
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
  if (dur > 3000 && dur < 6001)
  {
    limit = (dur-3000)/188;
    if (limit == 0) limit = 1;
    for (x=0; x<=limit; x++) {
      strip.setPixelColor(x, strip.Color(0, 255, 0));
    }
    for (x=limit+1; x<=15; x++) {
      strip.setPixelColor(x, strip.Color(0, 0, 255));
    }
  }
  
  //blue step - 3
  if (dur > 6000 && dur < 9001)
  {
    limit = (dur-6000)/188;
    if (limit == 0) limit = 1;
    for (x=0; x<=limit; x++) {
      strip.setPixelColor(x, strip.Color(0, 0, 255));
    }
    for (x=limit+1; x<=15; x++) {
      strip.setPixelColor(x, strip.Color(255, 0, 0));
    }
  }

  strip.show();
  
  /*
  Serial.print(dur);
  Serial.print(" | ");
  Serial.print(limit);
  Serial.print("\n");
  */
  delay(50);
}

