#include <Servo.h>
//Throttle servo
Servo acc;
int servopin = 9;
int accval = 0;
//Flow sensor
byte statusLed    = 13;
byte sensorInterrupt = 0;
byte sensorPin       = 2;
float calibrationFactor = 4.5;
volatile byte pulseCount;  
float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;
unsigned long oldTime;

void setup() {
pinMode(A0,INPUT);
Serial.begin(9600);
acc.attach(servopin);

pinMode(statusLed, OUTPUT);
digitalWrite(statusLed, HIGH);
pinMode(sensorPin, INPUT);
digitalWrite(sensorPin, HIGH);
pulseCount        = 0;
flowRate          = 0.0;
flowMilliLitres   = 0;
totalMilliLitres  = 0;
oldTime           = 0;
attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
}

void loop() {
  accval = map(analogRead(A0),0,77,0,180);
  if(accval >= 0)
  if(accval > 180)
  accval = 180;
  else
  accval;
acc.write(accval);
Serial.println("Throttle: " + (String)map(accval,0,180,0,100));
if((millis() - oldTime) > 1000)
  { 
    detachInterrupt(sensorInterrupt);
    flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;
    oldTime = millis();
    unsigned int frac;
    Serial.print("Flow rate: ");
    Serial.print(int(flowRate));
    Serial.print(".");
    frac = (flowRate - int(flowRate)) * 10;
    Serial.print(frac, DEC);
    Serial.print("L/min");
    Serial.print("  Current Liquid Flowing: ");
    Serial.print(flowMilliLitres);
    Serial.print("mL/Sec");
    Serial.print("  Output Liquid Quantity: ");
    Serial.print(totalMilliLitres);
    Serial.println("mL"); 
    pulseCount = 0;
    attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
  }
}
void pulseCounter()
{
  pulseCount++;
}
