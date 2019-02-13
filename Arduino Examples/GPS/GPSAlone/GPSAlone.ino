#include <SoftwareSerial.h>
#include <TinyGPS.h>
 
long lat,lon; // create variable for latitude and longitude object
 
SoftwareSerial gpsSerial(4, 5); // rx, tx create gps sensor connection
TinyGPS gps; // create gps object
 
void setup(){
  Serial.begin(9600); // connect serial
  gpsSerial.begin(9600); // connect gps sensor
      Serial.print("GPS Start");

}
 
void loop(){
  while(gpsSerial.available()){ // check for gps data
   if(gps.encode(gpsSerial.read())){ // encode gps data
    gps.get_position(&lat,&lon); // get latitude and longitude
    // display position
    Serial.print("Position: ");
    Serial.print("lat: ");Serial.print(lat);Serial.print(" ");// print latitude
    Serial.print("lon: ");Serial.println(lon); // print longitude
   }
  }
}
