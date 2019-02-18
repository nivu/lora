#include <SoftwareSerial.h>
SoftwareSerial loraSerial (2, 3); //rx 2 tx 3

int nodeId = 4; // YOur Node Id Here
String txCommand;
void setup() {
  loraSerial.begin(57600);
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  RN2483_init();
}

void loop() {
  int sensorValue = analogRead(A0);
  txCommand = "radio tx " + sensorValue;
  sendcmd(txCommand);
  delay(2000); //Scheduled Time Delay
  
  //loraSerial.listen();
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
