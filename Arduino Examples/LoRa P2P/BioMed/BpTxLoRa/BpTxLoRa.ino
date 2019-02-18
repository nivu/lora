#include <SoftwareSerial.h>

// RN2483
SoftwareSerial loraSerial (2, 3); //rx 2 tx 3

// Bp Sensor
SoftwareSerial bpSerial (6, 7); //rx 6 tx 7

// lora packet data
int nodeId = 4; // YOur Node Id Here
String tramsmitCommand = "";

void setup() {
  loraSerial.begin(57600);
  bpSerial.begin(9600);
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  RN2483_init();
}

void loop() {
  bpSerial.listen();

  while(loraSerial.available() > 0){
    String loraResponse = loraSerial.readStringUntil('\n');
    Serial.println(loraResponse);
  }

  while (bpSerial.available() > 0){
    String resp = bpSerial.readString();
    Serial.println(resp);
    // format 129, 107, 095
    String sys = resp.substring(0, 4);
    String dia = resp.substring(5, 9);
    String pul = resp.substring(10, 14);
    Serial.println("systole:" + sys + " diastole:" + dia + " pulse:" + pul);

    resp.trim();
    resp = "BP:" + resp;
    String s2h = strtohex(resp);
    Serial.println("strtohex");
    Serial.println(s2h);
    tramsmitCommand = "radio tx " + s2h;
    delay(500);
    sendmsg(tramsmitCommand);
  }
  
  Serial.println();
  delay(5000); //Scheduled Time Delay
}

void RN2483_init(){
  sendcmd("sys reset");
  sendcmd("radio set mod lora");
  sendcmd("radio set freq 868100000");
  sendcmd("radio set pwr 14");
  sendcmd("radio set sf sf12");
  sendcmd("radio set afcbw 125");
  sendcmd("radio set rxbw 250");
  sendcmd("radio set fdev 5000");
  sendcmd("radio set prlen 8");
  sendcmd("radio set crc on");
  sendcmd("radio set cr 4/8");
  sendcmd("radio set wdt 0");
  sendcmd("radio set sync 12");
  sendcmd("radio set bw 250");
  sendcmd("sys get hweui");
  sendcmd("mac pause");
}

void sendcmd(String data){
  loraSerial.listen();
  Serial.println(data);
  loraSerial.println(data);
  String loraResponse = loraSerial.readStringUntil('\n');
  Serial.println(loraResponse);
  delay(200);
}

void sendmsg(String data){
  loraSerial.listen();
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println(data);
  loraSerial.println(data);
  String loraResponse = loraSerial.readStringUntil('\n');
    Serial.println(loraResponse);
  String loraResponse2 = loraSerial.readStringUntil('\n');
    Serial.println(loraResponse2);
  digitalWrite(LED_BUILTIN, LOW);
  delay(200);
}

String strtohex(String data){
  String sh;
  char ch;
  for (int i=0;i<data.length();i++){
    ch = data.charAt(i);
    sh += String(ch,HEX);
  }
  return sh;
}

