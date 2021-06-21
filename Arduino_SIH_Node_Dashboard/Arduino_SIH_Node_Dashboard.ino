#include <SoftwareSerial.h>
#include <Servo.h>

Servo myservo;
void transmit();
void buttoncheck();
void leds();
void tacho();
void receive();

#define ignitionpin 8
#define turbopin  7
#define generatorpin  6
#define enginepin 2
#define ignitionledpin 5
#define engineledpin 4
#define airfilterledpin 3
#define servopin 9
int ignition = 0, turbo = 0, generator = 0, engine = 0, airfilter = 0;
int ignitionled = 0, throttle = 0;
int p0 = 0, p = 0;
String c1 = "";

SoftwareSerial mySerial(10, 11); // RX, TX

void setup() {
  
  Serial.begin(9600);
  mySerial.begin(9600);
  delay(100);
  myservo.attach(9);
  
  pinMode(ignitionpin , INPUT_PULLUP);
  pinMode(turbopin , INPUT_PULLUP);
  pinMode(generatorpin , INPUT_PULLUP);
  pinMode(enginepin , INPUT_PULLUP);
  pinMode(ignitionledpin , OUTPUT);
  pinMode(engineledpin , OUTPUT);
  pinMode(airfilterledpin , OUTPUT);
  digitalWrite(ignitionledpin , HIGH);
  digitalWrite(engineledpin , HIGH);
  digitalWrite(airfilterledpin , HIGH);
}

void loop() {
  receive();
  buttoncheck();
  leds();
  transmit(); 
  tacho();
}
 void transmit() {
    String s = "Z" + (String)ignition + (String)turbo + (String)generator + (String)engine;
    char buf[5];
    s.toCharArray(buf, 6);
    mySerial.write(buf);
    delay(5);
    Serial.println(buf);}

   void buttoncheck(){ 
   if(digitalRead(ignitionpin) == HIGH) ignition = 1;
   else ignition = 0;
   if(digitalRead(turbopin) == LOW) turbo = 1;
   else turbo = 0;
   if(digitalRead(generatorpin) == LOW) generator = 1;
   else generator = 0;
  if(digitalRead(enginepin) == HIGH) 
  { if (engine == 0) engine = 1;
   else engine = 0;
    delay(1000);}
 }

 void leds()
 {
  if(ignition == 1) digitalWrite(ignitionledpin , LOW);
  else digitalWrite(ignitionledpin , HIGH);
  if(engine == 1) digitalWrite(engineledpin , LOW);
  else digitalWrite(engineledpin , HIGH);
  if(airfilter == 1) digitalWrite(airfilterledpin , LOW);
  else digitalWrite(airfilterledpin , HIGH);
 }

 void tacho()
 {
  p = throttle;
  if(p >= p0) myservo.write(map(p,0,180,0,100));
  else {
    for (p; p <= p0; p -= 1) 
    {
    myservo.write(map(p,0,180,0,100));  
    receive();
    if(throttle > p0) break;           
    delay(15);
    } 
    p0 = p;
    }
 }

void receive(){
  while (mySerial.available()) {c1 = mySerial.readStringUntil('Z'); }
  ignitionled = ((String)c1.charAt(0)).toInt();
  airfilter = ((String)c1.charAt(1)).toInt();
  throttle = c1.substring(2).toInt();
}
