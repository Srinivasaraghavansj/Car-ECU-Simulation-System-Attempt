#include <SoftwareSerial.h>
#include <Servo.h>
Servo acc;
SoftwareSerial mySerial(10, 11); // RX, TX
int servopin = 9;
int throttle = 0;
int relaypin = 7;
bool engine = 0;
String c1 = "";

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(A0,INPUT);
  pinMode(relaypin,OUTPUT);
  digitalWrite(relaypin, HIGH);
  acc.attach(servopin);
}

void loop() {
  
  while (mySerial.available()) {c1 = mySerial.readStringUntil('Z'); }
  engine = ((String)c1.substring(0)).toInt();
  Serial.println((String)engine);
  
  if(engine == 1) digitalWrite(relaypin, LOW);
  else digitalWrite(relaypin, HIGH);
  
  throttle = map(analogRead(A0),0,1023,0,180);
  if(throttle <= 0) throttle = 0;
  if(throttle >= 0)
  if(throttle > 180) throttle = 180;
  else throttle;
  acc.write(throttle);
  
  //Serial.println((String)throttle);
  //Serial.println((String)analogRead(A0));
  
  String s = "Z" + (String)throttle;
  char buf[4];
    s.toCharArray(buf, 5);
    mySerial.write(buf); 
    Serial.println((String)buf);
    delay(5); 
 }
