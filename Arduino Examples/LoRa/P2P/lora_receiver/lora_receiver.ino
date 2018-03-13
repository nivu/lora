#include <SoftwareSerial.h>
SoftwareSerial loraSerial(2, 3); //rx 2 tx 3

String inputString = "";
int D7 = 7;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  loraSerial.begin(57600);
  pinMode(D7, OUTPUT);

  delay(2000);
  RN2483_init();
}

void loop() {
  sendcmd("radio rx 0");

  if (loraSerial.available()) {
    String resp = loraSerial.readString();
    Serial.println(String(resp));
  }
  delay(1000);
}

void RN2483_init() {

  sendcmd("sys reset");
  sendcmd("radio set mod lora");
  sendcmd("radio set freq 868100000");
  sendcmd("radio set pwr 14");
  sendcmd("radio set sf sf12");
  sendcmd("radio set afcbw 125");
  sendcmd("radio set rxbw 250");
  sendcmd("radio set fdev 5000");
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
  String resp = loraSerial.readStringUntil('\n');
  Serial.println(resp.length());
}
