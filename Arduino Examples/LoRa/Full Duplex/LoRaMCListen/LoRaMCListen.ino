#include <SoftwareSerial.h>
 
SoftwareSerial loraSerial (10, 9); //rx 2 tx 3
bool flag = true;

void setup() {
  Serial.begin(9600);
  loraSerial.begin(57600);
  pinMode(LED_BUILTIN, OUTPUT);
  RN2483_init();
}

void loop() {
  if(flag){
    loraSerial.println("radio rx 0");
  }
  flag = false;
  loraSerial.listen();
  while (loraSerial.available() > 0) {
    char inByte = loraSerial.read();
    Serial.write(inByte);
    flag = true;
 }
 delay(1000);
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

void sendcmd(String data) {
  Serial.println(data);
  loraSerial.println(data);
}




