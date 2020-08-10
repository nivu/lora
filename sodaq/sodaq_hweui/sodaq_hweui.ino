/**
 * Works with:
 * SODAQ Mbili
 * SODAQ Autonomo
 * SODAQ One
 * SODAQ Explorer
 *
 */

#define CONSOLE_STREAM SERIAL_PORT_MONITOR

#if defined(ARDUINO_SODAQ_EXPLORER)
#define LORA_STREAM Serial2
#else
#define LORA_STREAM Serial1
#endif

#define LORA_BAUD 57600
#define DEBUG_BAUD 57600

void setup() {
  // put your setup code here, to run once:
  // Enable LoRa module
  #if defined(ARDUINO_SODAQ_AUTONOMO)
  pinMode(BEE_VCC, OUTPUT);
  digitalWrite(BEE_VCC, HIGH); //set input power BEE high
  #endif

  //wait forever for the Serial Monitor to open
  while(!CONSOLE_STREAM);

  //Setup streams
  CONSOLE_STREAM.begin(DEBUG_BAUD);
  LORA_STREAM.begin(LORA_BAUD);

  #ifdef LORA_RESET
  //Hardreset the RN module
  pinMode(LORA_RESET, OUTPUT);
  digitalWrite(LORA_RESET, HIGH);
  delay(100);
  digitalWrite(LORA_RESET, LOW);
  delay(100);
  digitalWrite(LORA_RESET, HIGH);
  delay(1000);

  // empty the buffer
  LORA_STREAM.end();
  #endif
  LORA_STREAM.begin(57600);

  // get the Hardware DevEUI
  CONSOLE_STREAM.println("Get the hardware serial, sending \"sys get hweui\\r\\n\", expecting \"xxxxxxxxxxxxxxxx\", received: \"");
  delay(100);
  LORA_STREAM.println("sys get hweui");
  delay(100);

  char buff[16];
  memset(buff, 0, sizeof(buff));

  LORA_STREAM.readBytesUntil(0x20, buff, sizeof(buff));
  CONSOLE_STREAM.print(buff);

  CONSOLE_STREAM.println();
}

void loop() {
  // put your main code here, to run repeatedly:
}
