#include <Servo.h>
Servo acc;
int servopin = 9;
int accval = 0;
void setup() {
pinMode(A0,INPUT);
Serial.begin(9600);
acc.attach(servopin);
}

void loop() {
  accval = map(analogRead(A0),0,77,0,180);
  if(accval >= 0)
  if(accval > 180)
  accval = 180;
  else
  accval;
acc.write(accval);
Serial.println((String)accval);
Serial.println((String)analogRead(A0));
delay(15);
}
