#define CONSOLE_STREAM SerialUSB
#define LORA_STREAM Serial2

#define LORA_BAUD 57600
#define DEBUG_BAUD 57600

void setup() {
  // put your setup code here, to run once:
  //Setup streams
  CONSOLE_STREAM.begin(DEBUG_BAUD);
  LORA_STREAM.begin(LORA_BAUD);
}

void loop() {
  // put your main code here, to run repeatedly:
  LORA_STREAM.end();
  LORA_STREAM.begin(57600);
  // RESET LORA_MODULE
  pinMode(LORA_RESET, OUTPUT);
  digitalWrite(LORA_RESET, LOW);
  delay(100);
  digitalWrite(LORA_RESET, HIGH);
  delay(1000);
  CONSOLE_STREAM.println("Testing LoRa module, sending \"sys get hweui\\r\\n\", expecting \"RN2xxx\", received: \"");
  delay(100);
//  LORA_STREAM.println("sys reset");
//  delay(100);
  LORA_STREAM.println("sys get hweui");
  delay(100);

  char buff[7];
  memset(buff, 0, sizeof(buff));

  LORA_STREAM.readBytesUntil(0x20, buff, sizeof(buff));
  CONSOLE_STREAM.print(buff);
  CONSOLE_STREAM.print("\"...");

  CONSOLE_STREAM.println();

  delay(800);
}
