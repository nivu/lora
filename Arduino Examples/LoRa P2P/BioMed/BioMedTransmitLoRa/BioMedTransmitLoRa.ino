#include <SoftwareSerial.h>

// RN2483
SoftwareSerial loraSerial (2, 3); //rx 2 tx 3

// Temperature Sensor
SoftwareSerial tempSerial (4, 5); //rx 4 tx 5

// Bp Sensor
SoftwareSerial bpSerial (6, 7); //rx 6 tx 7

// To Hold Temp Sensor Data
unsigned char output[9];
unsigned char need[2];
unsigned char needd[2];

// lora packet data
int nodeId = 4; // YOur Node Id Here
String payload = "";
String tempPayload = "";
String bpPayload = "";
String tramsmitCommand = "";

void setup() {
  loraSerial.begin(57600);
  bpSerial.begin(9600);
  tempSerial.begin(115200);
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  RN2483_init();
}

void loop() {
  Serial.println("Temperature Sensor Listen");  
  tempPayload = readTemperature();
  Serial.println(tempPayload);

  bpSerial.listen();
  Serial.println(loraSerial.isListening());
  Serial.println(bpSerial.isListening());

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
    
    if (sys.toInt() > 60 && sys.toInt() < 200 && dia.toInt() > 30 && dia.toInt() < 150){
      //insertBpData(sys.toInt(), dia.toInt(), pul.toInt());
    }
  }

  if(tempPayload.length() > 0){
    String s2h = strtohex(tempPayload);
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


String readTemperature(){
  tempSerial.listen();
  float targetTempF;
  float ambientTempF;
  delay(200);
  while(tempSerial.available())
    tempSerial.read();
  tempSerial.write(0xA5);
  tempSerial.write(0x15);
  tempSerial.write(0xBA);
   
  for (int counter = 0; counter <= 8; counter++){
    output[counter] = (unsigned char)tempSerial.read();
//    Serial.print(counter);
//    Serial.print(" ");
//    Serial.println(output[counter]);
  }
  if (output[1] == 0x5A && output[2] == 0x5A && output[3] == 0x45){
    need[0] = output[5];
    need[1] = output[6];
    needd[0] = output[7];
    needd[1] = output[8];
    float targetTempC = (float)(need[0] << 8 | need[1]) / 100;
    float ambientTempC = (float)(needd[0] << 8 | needd[1]) / 100;

    targetTempF = (targetTempC * 1.8) + 32;
    ambientTempF = (ambientTempC * 1.8) + 32;
  }
  
  if (output[0] == 0x5A && output[1] == 0x5A && output[2] == 0x45){
    need[0] = output[4];
    need[1] = output[5];
    needd[0] = output[6];
    needd[1] = output[7];
    float targetTempC = (float)(need[0] << 8 | need[1]) / 100;
    float ambientTempC = (float)(needd[0] << 8 | needd[1]) / 100;

    targetTempF = (targetTempC * 1.8) + 32;
    ambientTempF = (ambientTempC * 1.8) + 32;
  }
  return "TT:" +String(targetTempF) + ",AT:" + String(ambientTempF);
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

