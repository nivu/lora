#include <rn2xx3.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>

SoftwareSerial mySerial(2, 3); // RX, TX

rn2xx3 myLora(mySerial);
  
long lat,lon; // create variable for latitude and longitude object
unsigned long gdate, gtime;
 
SoftwareSerial gpsSerial(4, 5); // rx, tx create gps sensor connection
TinyGPS gps; // create gps object

void setup(){

  //output LED pin
  pinMode(13, OUTPUT);
  led_on();

  gpsSerial.begin(9600); // connect gps sensor
  Serial.print("GPS Start");

  Serial.begin(9600); //serial port to computer
  mySerial.begin(57600); //serial port to radio
  Serial.println("Startup");

  initialize_radio();                        

  myLora.tx("ping");

  led_off();
  delay(2000);
}

void initialize_radio(){
  //reset rn2483
  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);
  delay(500);
  digitalWrite(12, HIGH);

  delay(100); //wait for the RN2xx3's startup message
  mySerial.flush();

  //Autobaud the rn2483 module to 9600. The default would otherwise be 57600.
  myLora.autobaud();
  /* 
DR0 SF12
DR1 SF11
DR2 SF10
DR3 SF9
DR4 SF8
DR5 SF7
  */
  myLora.setDR(0); // sf12, bw 125khz, bps 250 

  //check communication with radio
  String hweui = myLora.hweui();
  while(hweui.length() != 16){
    Serial.println("Communication with RN2xx3 unsuccessful. Power cycle the board.");
    Serial.println(hweui);
    delay(10000);
    hweui = myLora.hweui();
  }

  //print out the HWEUI so that we can register it via ttnctl
  Serial.println("When using OTAA, register this DevEUI: ");
  Serial.println(myLora.hweui());
  Serial.println("RN2xx3 firmware version:");
  Serial.println(myLora.sysver());

  //configure your keys and join the network
  Serial.println("Trying to join loraserver");
  bool join_result = false;

  /*
   * ABP: initABP(String addr, String AppSKey, String NwkSKey);
   * Paste the example code from the TTN console here:
   */

  // Keys Node 096f 
  const char *devAddr = "003b1e85";
  const char *nwkSKey = "6e1b145a7df6f5d07db74c59b8790ce6";
  const char *appSKey = "ae12e52276e3e94220015e8f021fc752";

  join_result = myLora.initABP(devAddr, appSKey, nwkSKey);

  while(!join_result){
    Serial.println("Unable to join. Are your keys correct, and do you have TTN coverage?");
    delay(60000); //delay a minute before retry
    join_result = myLora.init();
  }
  Serial.println("Successfully joined loraserver");

}

// the loop routine runs over and over again forever:
void loop(){
    led_on();
    readGps();
    String data = String(lat) + "," + String(lon) + "," + String(gtime);
    Serial.println("TXing " + data);
    int tx = myLora.txCnf(data); //one byte, blocking function

    if(tx == 0){
        Serial.println("TX_FAIL");
    } else if(tx == 1){
        Serial.println("TX_SUCCESS");
    } else if(tx == 2){
        Serial.println("TX_WITH_RX");
        String received = myLora.getRx();
        received = myLora.base16decode(received);
        Serial.println("Received downlink: " + received);
    }
    led_off();
    delay(5000);
}


void readGps() {
    Serial.println("Reading GPS Coordinates");
    gpsSerial.listen();
    delay(500);

    while(gpsSerial.available()){ // check for gps data
        if(gps.encode(gpsSerial.read())){ // encode gps data
            gps.get_position(&lat,&lon); // get latitude and longitude
            gps.get_datetime(&gdate, &gtime);
            // display position
            Serial.print("Position: ");
            Serial.print("lat: ");Serial.print(lat);Serial.print(" ");// print latitude
            Serial.print("lon: ");Serial.print(lon);Serial.print(" "); // print longitude
            Serial.print("time: ");Serial.println(gtime);
        }
    }
}

void led_on(){
  digitalWrite(13, 1);
}

void led_off(){
  digitalWrite(13, 0);
}


