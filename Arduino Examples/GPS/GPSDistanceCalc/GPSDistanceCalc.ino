//Works fine when GPS in Active mode
#include <SoftwareSerial.h>
#include <TinyGPS.h>

long lat,lon;
SoftwareSerial gpsSerial(3,4);//rx,tx 
TinyGPS gps;

double citLat = 11.022723; // Input Location 1
double citLng = 77.026892; // Input Location 1

double gctLat = 11.020893; // Input Location 2
double gctLng = 76.939142; // Input Location 2

int nodeId = 1;

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600); // connect to gps  
  Serial.println("GPS Start");

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(10, OUTPUT);
}

void loop() { 
 
  while(gpsSerial.available()){ // check for gps data
   if(gps.encode(gpsSerial.read())){ // encode gps data
    gps.get_position(&lat,&lon); // get latitude and longitude
    double dlat = lat; // type casting
    double gpslat = dlat/1000000;

    double dlon = lon; // type casting
    double gpslon = dlon/1000000;

    //get distance between two coordinates
    int dist = getDistanceFromLatLonInKm(gctLat, gctLng, gpslat, gpslon);
    Serial.println(dist);

    // if distance is less than 30m do some action
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



