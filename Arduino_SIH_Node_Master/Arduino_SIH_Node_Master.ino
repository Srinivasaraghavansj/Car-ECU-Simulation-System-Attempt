#include <SoftwareSerial.h>

SoftwareSerial esc(6, 5); // RX, TX
SoftwareSerial sen(9, 3); // RX, TX
SoftwareSerial dash(10, 11); // RX, TX

String c1 = "" , c2 = "" ,c3 = "";


int ignition = 0, turbo = 0, generator = 0, engine = 0, airfilter = 0;
int ignitionled = 0, throttle = 0;
long int pressure = 0, flow = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial) {;}
  esc.begin(9600);
  sen.begin(9600);
  dash.begin(9600);
}

void loop() {
  receivesensors();
  receivedash();
  receiveesc();
  transmitdash();
  transmitesc();
  }

  void receivedash(){
  dash.listen();
  delay(10);
  while (dash.available()) {c3 = dash.readStringUntil('Z');}
  ignition = ((String)c3.charAt(1)).toInt();
  turbo = ((String)c3.charAt(1)).toInt();
  generator = ((String)c3.charAt(2)).toInt();
  engine = ((String)c3.charAt(3)).toInt();
  Serial.println("Dash RX : ign,turbo,gen,eng " + (String)ignition + " " + (String)turbo + " " + (String)generator + " " + (String)engine + "   " + c3);
  }

  
  void transmitdash(){
    dash.listen();
    String s = "Z" + (String)ignitionled + (String)airfilter + (String)throttle;
    char buf[6];
    s.toCharArray(buf, 7);
    dash.write(buf);
    Serial.println("Dash TX: Ignition,airfilter,throttle  " + (String)buf);
    delay(5);
  }

  void receiveesc(){
  esc.listen();
  delay(10);
  while (esc.available()) {c1 = esc.readStringUntil('Z');}
  /*throttle = 0;
  for(int i = 0; i < c1.length() ; i++)
  throttle = (throttle*10) + ((String)c1.charAt(i)).toInt() ;*/
  throttle = c1.substring(0).toInt();
  Serial.println("ESC RX: Throttle " + (String)throttle);
  }

  void transmitesc(){
    esc.listen();
    String s = "Z" + (String)engine;
    char buf[2];
    s.toCharArray(buf, 3 );
    dash.write(buf);
    Serial.println("ESC TX: Engine  " + (String)buf);
    delay(5);
  }

  void receivesensors(){
    sen.listen();
    delay(10);
    while (sen.available()) {c2 = sen.readStringUntil('Z'); }
    pressure = (int)((String)(c2.substring(0,4).concat("0")).toInt());
    flow = (int)((c2.substring(8)).toInt());
    Serial.println("SEN RX: P: " + (String)pressure + "  F: " + (String)flow + "  " +c2);
    Serial.println(pressure);
  }
