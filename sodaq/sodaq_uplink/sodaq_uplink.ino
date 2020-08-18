#include <Sodaq_RN2483.h>

#define debugSerial SerialUSB
#define loraSerial Serial2

// USE YOUR OWN KEYS!
const uint8_t devAddr[4] =
{
  // TTN 0x26, 0x04, 0x1A, 0xAF
  0x00, 0x03, 0xcc, 0xbd
};

// USE YOUR OWN KEYS!
const uint8_t appSKey[16] =
{
// TTN  0X68, 0x81, 0x92, 0xEB, 0x01, 0x5B, 0x55, 0x1B, 0xE0, 0x5C, 0x2A, 0x34, 0x95, 0x49, 0x42, 0x9E

  0xc3 , 0X60 , 0X92 , 0X4e , 0Xef , 0X37 , 0X15 , 0Xb7 , 0Xf8 , 0X03 , 0X97 , 0Xfc , 0Xf6 , 0X3c , 0X4c , 0X57

};

// USE YOUR OWN KEYS!
const uint8_t nwkSKey[16] =
{
  // TTN 0X12, 0xC2, 0xE5, 0xAA, 0x38, 0xBF, 0x49, 0x1D, 0x38, 0x0C, 0xEB, 0xA5, 0xE6, 0x4C, 0xF8, 0x29

    0X46, 0Xb9, 0X62, 0Xcb, 0X0d, 0Xf9, 0X87, 0Xee, 0X3b, 0Xe9, 0X08, 0X8d, 0X64, 0X88, 0X85, 0X13

};

//const char *devAddr = "26041AAF";
//const char *nwkSKey = "12C2E5AA38BF491D380CEBA5E64CF829";
//const char *appSKey = "688192EB015B551BE05C2A349549429E";

// Some complete random hex
uint8_t testPayload[] =
{
  0x53, 0x4F, 0x44, 0x41, 0x51
};

void setup()
{
  while ((!debugSerial) && (millis() < 10000));

  debugSerial.begin(57600);
  loraSerial.begin(LoRaBee.getDefaultBaudRate());
//
//  debugSerial.println("Setting Spreading Factor");
//  LoRaBee.setSpreadingFactor(7);
//  delay(100);

  LoRaBee.setMacParam("ch dcycle 3",9); 

  LoRaBee.setDiag(debugSerial); // optional

  if (LoRaBee.initABP(loraSerial, devAddr, appSKey, nwkSKey, false))
  {
    debugSerial.println("Connection to the network was successful.");
  }
  else
  {
    debugSerial.println("Connection to the network failed!");
  }

 // Uncomment this line to for the RN2903 with the Actility Network
 // For OTAA update the DEFAULT_FSB in the library
 // LoRaBee.setFsbChannels(1);

}

void loop()
{
  debugSerial.println("Sleeping for 5 seconds before starting sending out test packets.");
  for (uint8_t i = 5; i > 0; i--)
  {
    debugSerial.println(i);
    delay(1000);
  }

  // send 10 packets, with at least a 5 seconds delay after each transmission (more seconds if the device is busy)
  uint8_t i = 10;
  while (i > 0)
  {
    switch (LoRaBee.send(1, testPayload, 5))
    {
    case NoError:
      debugSerial.println("Successful transmission.");
      i--;
      break;
    case NoResponse:
      debugSerial.println("There was no response from the device.");
      break;
    case Timeout:
      debugSerial.println("Connection timed-out. Check your serial connection to the device! Sleeping for 20sec.");
      delay(20000);
      break;
    case PayloadSizeError:
      debugSerial.println("The size of the payload is greater than allowed. Transmission failed!");
      break;
    case InternalError:
      debugSerial.println("Oh No! This shouldn't happen. Something is really wrong! Try restarting the device!\r\nThe program will now halt.");
      while (1) {};
      break;
    case Busy:
      debugSerial.println("The device is busy. Sleeping for 10 extra seconds.");
      delay(10000);
      break;
    case NetworkFatalError:
      debugSerial.println("There is a non-recoverable error with the network connection. You should re-connect.\r\nThe program will now halt.");
      while (1) {};
      break;
    case NotConnected:
      debugSerial.println("The device is not connected to the network. Please connect to the network before attempting to send data.\r\nThe program will now halt.");
      while (1) {};
      break;
    case NoAcknowledgment:
      debugSerial.println("There was no acknowledgment sent back!");
      break;
    default:
      break;
    }
    delay(10000);
  }
}
