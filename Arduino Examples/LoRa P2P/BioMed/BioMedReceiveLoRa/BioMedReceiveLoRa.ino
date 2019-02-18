#include <SoftwareSerial.h>
 
SoftwareSerial loraSerial (2, 3); //rx 2 tx 3
bool flag;

void setup() {
  Serial.begin(9600);
  loraSerial.begin(57600);
  pinMode(LED_BUILTIN, OUTPUT);
  RN2483_init();
  flag = true;
}

void loop() {
  if(flag){
    loraSerial.println("radio rx 0");
    //flag = false;
  }
  while (loraSerial.available() > 0) {
    String loraResponse = loraSerial.readStringUntil('\n');
    Serial.println(loraResponse);
    if(loraResponse.indexOf("radio_rx") == 0){
      loraResponse.replace("radio_rx", "");
      loraResponse.trim();
      loraResponse.toLowerCase();
      Serial.println(loraResponse);
      String str = hextostr(loraResponse);
      Serial.println(str);
    }
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
  loraSerial.listen();
  Serial.println(data);
  loraSerial.println(data);
  String loraResponse = loraSerial.readStringUntil('\n');
  Serial.println(loraResponse);
  delay(200);
}

String strtohex(String data){
  String sh;
  char ch;
  Serial.println();
  Serial.println(data);
  Serial.println("len : " + data.length());
  for (int i=0;i<data.length();i++){
    ch = data.charAt(i);
    sh += String(ch,HEX);
    Serial.println(ch + " = " + String(ch,HEX));
  }
  return sh;
}

String hextostr(String data){
  String sh;char ch;
  String msbStr;String lsbStr;
  short msb;short lsb;
  short msbByte;
  
  for (int i=0; i < data.length(); i+=2){
    msbStr = hexVal(data.charAt(i));
    lsbStr = hexVal(data.charAt(i+1));
    msb = (short) msbStr.toInt(); 
    lsb = (short) lsbStr.toInt();
    msbByte = msb << 4;
    ch = char(msbByte | lsb);
    sh += String(ch);
  }
  return sh;
}

String hexVal(char data){
  String ret = "";
   
  switch (data) {
    case 'a':
      ret = "10"; 
      break;
    case 'b':
      ret = "11";
      break;
    case 'c':
      ret = "12";
      break;
    case 'd':
      ret = "13";
      break;
    case 'e':
      ret = "14";
      break;
    case 'f':
      ret = "15";
      break;
    default:
    ret = data;
    break;
  }

  return ret;

}
