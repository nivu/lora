//Open Serial Port and Send HEX Data
#include <SoftwareSerial.h>
SoftwareSerial loraSerial (2, 3); //rx 2 tx 3
int nodeId = 9;
void setup() {
  loraSerial.begin(57600);
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  RN2483_init();
}

void loop() {
  while(Serial.available() > 0){
    String data = Serial.readString();
    String is;
    is = String(data);
    is = "radio tx " + is;
    sendmsg(is);
    delay(1000);
  }
  
  loraSerial.listen();
  while(loraSerial.available() > 0){
    char loraResponse = loraSerial.read();
    Serial.write(loraResponse);
  }

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
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println(data);
  loraSerial.println(data); 
  digitalWrite(LED_BUILTIN, LOW);
}

void sendmsg(String data){
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println(data);
  loraSerial.println(data);
  digitalWrite(LED_BUILTIN, LOW);  
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
