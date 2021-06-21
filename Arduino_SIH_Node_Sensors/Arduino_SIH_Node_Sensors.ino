#include <SoftwareSerial.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#define BMP_SCK 13
#define BMP_MISO 12
#define BMP_MOSI 11 
#define BMP_CS 10
Adafruit_BMP280 bme;

SoftwareSerial mySerial(10, 11);

byte statusLed    = 13;
byte sensorInterrupt = 0;
byte sensorPin       = 2;
float calibrationFactor = 4.5;
volatile byte pulseCount;  
float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;
unsigned long oldTime;
String fml = "";
String pressure = "";
  
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  while(!bme.begin(0x76)){Serial.println("NOT SENSOR"); delay(100);};
  delay(1000);
  pinMode(sensorPin, INPUT);
  digitalWrite(sensorPin, HIGH);
  pulseCount        = 0;
  flowRate          = 0.0;
  flowMilliLitres   = 0;
  oldTime           = 0;
  attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
}
  
void loop() {
    if((millis() - oldTime) > 500){ 
    detachInterrupt(sensorInterrupt);
    flowRate = ((500.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;
    flowMilliLitres = (flowRate / 60) * 500;
    fml = (String)flowMilliLitres + "";
    oldTime = millis();
    unsigned int frac;
    //Serial.println((String)flowMilliLitres); 
    pulseCount = 0;
    attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
    }
    
   pressure = ((String)bme.readPressure()).substring(0,5);
   String s = "Z" + pressure + fml;
   //Serial.println(s);
   char buf[11];
   s.toCharArray(buf, 12);
   mySerial.write(buf);
   Serial.println(buf);
   delay(5);
}
void pulseCounter(){pulseCount++;}
