#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define LEDPIN 2
#define TRIGPIN 5
#define ECHOPIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, LEDPIN, NEO_GRB + NEO_KHZ800);
long durPrec = 0;

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
  int num, limit, x, nloop;
  long dur;

  if (durPrec == 0)
  {
    durPrec = RangeRead();
    delay(5);
    durPrec = RangeRead();
    delay(5);
    durPrec = RangeRead();
    delay(5);
    durPrec = RangeRead();
    delay(5);
  }

  nloop = 0;
  do
  {
    nloop++;
    delayMicroseconds(300);
    dur = RangeRead();
    Serial.print("dur:");
    Serial.print(dur);
    Serial.print(" min:");
    Serial.print(durPrec*0.95);
    Serial.print(" max:");
    Serial.print(durPrec*1.05);
    Serial.print("\n");
  } while (((dur < (durPrec*0.85)) || (dur > (durPrec*1.15))) && nloop < 6);

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

  durPrec = dur;
  Serial.print("end\n");
  delay(20);
}

long RangeRead() {
  long dur, total;
  int x;
  int NumReads = 15;
  int ReadQty = 0;

  dur = 0;
  total = 0;
  for (x=0; x<NumReads; x++) {
    digitalWrite(TRIGPIN, LOW);
    delayMicroseconds(5);
    digitalWrite(TRIGPIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGPIN, LOW);
    dur = pulseIn(ECHOPIN, HIGH);
    if ((total == 0) || (dur > (((total/ReadQty)*0.90)) && (dur < ((total/ReadQty)*1.10))))
    {
      total = total + dur;
      ReadQty++;
      /*
      Serial.print(ReadQty);
      Serial.print(": ");
      Serial.print(dur);
      Serial.print(" ");
      */
    }
  }

  return total/ReadQty;
}
