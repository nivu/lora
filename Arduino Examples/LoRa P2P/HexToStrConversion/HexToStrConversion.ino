void setup() {
  Serial.begin(9600);
}

void loop() {
  String tempPayload = "t89.65";
  String s2h = strtohex(tempPayload);
  Serial.println("strtohex");
  Serial.println(s2h);

  String resp = "39322E3236";
  resp.toLowerCase();
  String h2s = hextostr(resp);
  Serial.println("hextostr");
  Serial.println(h2s);

  // helper code
  int valu = (int) 't';
  Serial.println("******");
  Serial.println(valu);
  String msbStr = "7";
  String lsbStr = "4";
  short msb = (short) msbStr.toInt();
  short lsb = (short) lsbStr.toInt();
  short msbByte = msb << 4;
  Serial.println("!!!!");
  Serial.println(msbByte|lsb);
  char var2 = char(msbByte|lsb);
  Serial.println("######");
  Serial.println(var2);
  Serial.println();

  delay(3000);
}

String strtohex(String data){
  String sh;
  char ch;
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

