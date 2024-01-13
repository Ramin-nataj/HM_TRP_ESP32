/*
  Serial Event example

  When new serial data arrives, this sketch adds it to a String.
  When a newline is received, the loop prints the string and clears it.

  A good test for this is to try it with a GPS receiver that sends out
  NMEA 0183 sentences.

  NOTE: The serialEvent() feature is not available on the Leonardo, Micro, or
  other ATmega32U4 based boards.

  created 9 May 2011
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/SerialEvent
*/

#define Pin_CONFIG 5
// #define Pin_ENABLE 6
#define Pin_LED 2


uint32_t hexValue = 0xAA;                                                 // 0xAAFAD2DD1800;
uint8_t Set_Reset[3] = { 0xAA, 0xFA, 0xF0 };                              //Reset to default parameter
uint8_t Set_Reading[3] = { 0xAA, 0xFA, 0xE1 };                            //Reading the current Config parameter
uint8_t Set_frequency[7] = { 0xAA, 0xFA, 0xD2, 0x19, 0xDD, 0x18, 0x00 };  //433.92
uint8_t Set_drate[7] = { 0xAA, 0xFA, 0xC3, 0x00, 0x00, 0x25, 0x80 };      //set up transfer speed as 9600bps
uint8_t Set_bandwidth[5] = { 0xAA, 0xFA, 0xB4, 0x00, 0x6E };              //110KHZ
uint8_t Set_deviation[4] = { 0xAA, 0xFA, 0xA5, 0x28 };                    //set up modulation frequency as 40KHz
uint8_t Set_level[4] = { 0xAA, 0xFA, 0x96, 0x03 };                        //set up transmission power as level 3 (+8 dBm)

uint8_t inByte;



String inputString = "";      // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete


void setup() {
  // initialize serial:
  Serial.begin(115200);

  Serial2.begin(9600, SERIAL_8N1, 16, 17);  // UART2 at 9600 bps, 8 data bits, no parity, 1 stop bit

  pinMode(Pin_LED, OUTPUT);     // Led pin
  pinMode(Pin_CONFIG, OUTPUT);  // Led pin
  // pinMode(Pin_ENABLE, OUTPUT);  // Led pin

  //
  digitalWrite(Pin_CONFIG, LOW);
  // digitalWrite(Pin_ENABLE, HIGH);

  delay(500);
  // delay(1000);
  // for (int i = 0; i < sizeof(Set_frequency); i++) {
  //   Serial2.print(Set_frequency[i], HEX);  // Set up working frequency
  // }
  //Serial2.println();
  Serial2.write(Set_Reset, sizeof(Set_Reset));
  Serial2.println();
  delay(500);
  Serial2.write(Set_frequency, sizeof(Set_frequency));
  Serial2.println();
  delay(500);
  Serial2.write(Set_drate, sizeof(Set_drate));  //Set up wireless data rate
  Serial2.println();
  delay(500);
  Serial2.write(Set_bandwidth, sizeof(Set_bandwidth));  // Set up receiving bandwidth
  Serial2.println();
  delay(500);
  Serial2.write(Set_deviation, sizeof(Set_deviation));  // set up modulation frequency as 40KHz
  Serial2.println();
  delay(500);
  Serial2.write(Set_level, sizeof(Set_level));  //Set up transmission power
  Serial2.println();
  delay(500);
  Serial2.write(Set_Reading, sizeof(Set_Reading));  //Set up transmission power
  Serial2.println();
  // delay(500);
  digitalWrite(Pin_CONFIG, HIGH);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    Serial.println(inputString);
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial2.available()) {
    // get the new byte:
    char inChar = (char)Serial2.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
