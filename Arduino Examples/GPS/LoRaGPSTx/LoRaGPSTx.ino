// Three Serial ports
#include <SoftwareSerial.h>
#include <TinyGPS.h>

long lat,lon;
 
SoftwareSerial loraSerial (2, 3); //rx 2 tx 3
SoftwareSerial gpsSerial(8,9);//rx,tx 

TinyGPS gps;

double homeLat = 11.021020;
double homeLng = 76.937812;

double gctLat = 11.020893;
double gctLng = 76.939142;

int nodeId = 9;

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600); // connect gps sensor 
  loraSerial.begin(57600);
  pinMode(LED_BUILTIN, OUTPUT);
  RN2483_init();
  gpsSerial.listen();
}

void loop() {
  while(gpsSerial.available() > 0){ // check for gps data
   if(gps.encode(gpsSerial.read())){ // encode gps data
    gps.get_position(&lat,&lon); // get latitude and longitude
    double vlat = lat;
    double dlat = vlat/1000000;
    double vlon = lon;
    double dlon = vlon/1000000;
    int dist = getDistanceFromLatLonInKm(gctLat, gctLng, dlat , dlon);
    //Serial.println(dist);
    String isss = "radio tx " + String(dist);
    sendmsg(isss);
    loraSerial.listen();
    delay(1000);
   }
  }
  while(loraSerial.available() > 0){
    char loraResponse = loraSerial.read();
    Serial.write(loraResponse);
    gpsSerial.listen();
  }

}

int getDistanceFromLatLonInKm(double lat1,double lon1,double lat2, double lon2) {
  double R = 6371; // Radius of the earth in km
  double dLat = deg2rad(lat2-lat1);  // deg2rad below
  double dLon = deg2rad(lon2-lon1); 
  double a = sin(dLat/2) * sin(dLat/2) + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * sin(dLon/2) * sin(dLon/2); 
  double c = 2 * atan2(sqrt(a), sqrt(1-a)); 
  int d = R * c * 1000; // Distance in m
  return d;
}

double deg2rad(double deg) {
  return deg * (PI/180);
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


