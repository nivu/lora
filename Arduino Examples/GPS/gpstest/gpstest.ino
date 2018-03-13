
#include <SoftwareSerial.h>
#include <TinyGPS.h>

long lat,lon;
 
TinyGPS gps;

double homeLat = 11.021020;
double homeLng = 76.937812;

double gctLat = 11.020893;
double gctLng = 76.939142;

int nodeId = 1;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
    pinMode(10, OUTPUT);

}

void loop() { 
 
  while(Serial.available()){ // check for gps data
   if(gps.encode(Serial.read())){ // encode gps data
    gps.get_position(&lat,&lon); // get latitude and longitude
    double vlat = lat;
    double dlat = vlat/1000000;
    double vlon = lon;
    double dlon = vlon/1000000;
    int dist = getDistanceFromLatLonInKm(homeLat, homeLng, dlat , dlon);
    Serial.println(dist);
    if(dist < 30){
      digitalWrite(LED_BUILTIN, 1);
            digitalWrite(10, 1);

      delay(3000);
      digitalWrite(LED_BUILTIN, 0);
            digitalWrite(10, 0);

    }

   }
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



