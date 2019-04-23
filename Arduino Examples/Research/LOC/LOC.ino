#include <rn2xx3.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

rn2xx3 myLora(mySerial);
  
void setup(){

  //output LED pin
  pinMode(13, OUTPUT);
  led_on();

  Serial.begin(9600); //serial port to computer

  delay(500);
  
  mySerial.begin(57600); //serial port to radio
  Serial.println("Startup");

  initialize_radio();                        

  myLora.tx("ping");

  led_off();
  delay(2000);
}

void initialize_radio(){
  //reset rn2483
  pinMode(10, OUTPUT);
  digitalWrite(10, LOW);
  delay(500);
  digitalWrite(10, HIGH);

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

  // Keys Node ebcf
  const char *devAddr = "01309a7c";
  const char *nwkSKey = "0853a12b7e912596accc15e473c7ad23";
  const char *appSKey = "457089a035e67cea6a1e37044bceac7c";

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

  for(int dr = 0; dr < 6; dr++){
    myLora.setDR(dr); 
    delay(3000);

    for(int i = 1; i < 51; i++) {
        led_on();
        
        String data = "LOC" + String(i);
        //String data = "SVP" + String(i);

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
        delay(3000);
    }
  }

}

void led_on(){
  digitalWrite(13, 1);
}

void led_off(){
  digitalWrite(13, 0);
}

