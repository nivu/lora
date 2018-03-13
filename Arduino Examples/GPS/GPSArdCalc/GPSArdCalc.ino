
#include <SoftwareSerial.h>
double lat1 = 45.45 ;
double lon1 = 30.20;
double lat2 = 45.45 ;
double lon2 = 30.20;

double deg2rad(double deg);
int getDistanceFromLatLonInKm(double lat1,double lon1,double lat2, double lon2);

void setup() {
  Serial.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

Serial.print(getDistanceFromLatLonInKm(11.021020, 76.937812 , 11.020893, 76.939142));

}

void loop() { // run over and over

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

