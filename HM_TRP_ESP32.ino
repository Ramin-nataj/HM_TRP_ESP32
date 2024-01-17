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
#define Pin_ENABLE 18
#define Pin_LED 2


uint32_t hexValue = 0xAA;                                                 // 0xAAFAD2DD1800;
uint8_t Set_Reset[3] = { 0xAA, 0xFA, 0xF0 };                              //Reset to default parameter
uint8_t Set_Reading[3] = { 0xAA, 0xFA, 0xE1 };                            //Reading the current Config parameter
uint8_t Set_frequency[7] = { 0xAA, 0xFA, 0xD2, 0x19, 0xDD, 0x18, 0x00 };  //433.92
uint8_t Set_drate[7] = { 0xAA, 0xFA, 0xC3, 0x00, 0x00, 0x25, 0x80 };      //set up transfer speed as 9600bps
//
// uint8_t Set_bandwidth[5] = { 0xAA, 0xFA, 0xB4, 0x00, 0x69 };              //105KHZ
// uint8_t Set_bandwidth[5] = { 0xAA, 0xFA, 0xB4, 0x00, 0x6E };                  //110KHZ
// uint8_t Set_bandwidth[5] = { 0xAA, 0xFA, 0xB4, 0x00, 0x73 };              //115.0KHZ
uint8_t Set_bandwidth[5] = { 0xAA, 0xFA, 0xB4, 0x03, 0x31 };              //817.0KHZ
//
// uint8_t Set_deviation[4] = { 0xAA, 0xFA, 0xA5, 0x50 };                    //Set up frequency deviation as 80KHz
// uint8_t Set_deviation[4] = { 0xAA, 0xFA, 0xA5, 0x2D };  //Set up frequency deviation as 45KHz
uint8_t Set_deviation[4] = { 0xAA, 0xFA, 0xA5, 0x28 };                    //Set up frequency deviation as 40KHz
//
// uint8_t Set_level[4] = { 0xAA, 0xFA, 0x96, 0x03 };                        //set up transmission power as level 3 (+8 dBm)
uint8_t Set_level[4] = { 0xAA, 0xFA, 0x96, 0x07 };                        //set up transmission power as level 3 (+20 dBm)
//
uint8_t Set_UARTdrate[7] = { 0xAA, 0xFA, 0x1E, 0x00, 0x00, 0x25, 0x80 };  //Set up UART transfer speed speed as 9600bps
uint8_t Set_signalStr[3] = { 0xAA, 0xFA, 0x87 };                          //Wireless signal strength when receiving useful data
uint8_t Set_Disturb[3] = { 0xAA, 0xFA, 0x78 };                            //Disturb wireless signal strength

uint8_t Set_Reciver[3] = { 0xAA, 0xFA, 0xE1 };                            //Disturb wireless signal strength

uint8_t inByte;
int buffer[64];
int count = 0;
String inputString = "";      // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
void clearBufferArray();      // function to clear buffer array


void setup() {
  // initialize serial:
  Serial.begin(9600);

  Serial2.begin(9600, SERIAL_8N1, 16, 17);  // UART2 at 9600 bps, 8 data bits, no parity, 1 stop bit

  pinMode(Pin_LED, OUTPUT);     // Led pin
  pinMode(Pin_CONFIG, OUTPUT);  // Led pin
  pinMode(Pin_ENABLE, OUTPUT);  // Led pin

  //
  digitalWrite(Pin_CONFIG, LOW);
  digitalWrite(Pin_ENABLE, LOW);

  delay(500);
  // delay(1000);
  // for (int i = 0; i < sizeof(Set_frequency); i++) {
  //   Serial2.print(Set_frequency[i], HEX);  // Set up working frequency
  // }
  //Serial2.println();


  Serial2.write(Set_Reset, sizeof(Set_Reset));
  // Serial2.println();
  delay(250);
  Serial2.write(Set_frequency, sizeof(Set_frequency));
  // Serial2.println();
  delay(250);
  Serial2.write(Set_drate, sizeof(Set_drate));  //Set up wireless data rate
  // Serial2.println();
  delay(250);
  Serial2.write(Set_bandwidth, sizeof(Set_bandwidth));  // Set up receiving bandwidth
  // Serial2.println();
  delay(250);
  Serial2.write(Set_deviation, sizeof(Set_deviation));  // set up modulation frequency as 40KHz
  // Serial2.println();
  delay(250);
  Serial2.write(Set_level, sizeof(Set_level));  //Set up transmission power
  // Serial2.println();
  // delay(250);
  // Serial2.write(Set_UARTdrate, sizeof(Set_UARTdrate));  //
  // Serial2.println();
  delay(250);
  Serial2.write(Set_signalStr, sizeof(Set_signalStr));  //
  // Serial2.println();
  delay(250);
  Serial2.write(Set_Disturb, sizeof(Set_Disturb));  //
  // Serial2.println();
  delay(250);
  Serial2.write(Set_Reading, sizeof(Set_Reading));  //Set up transmission power
  // Serial2.println();
  delay(67);
  Serial.println((char)Serial2.read());

  delay(250);

  digitalWrite(Pin_CONFIG, HIGH);  //	Set low for configuration mode (connect to GND). Set high for communication (Default is high).
    delay(50);
  digitalWrite(Pin_ENABLE, LOW);   //Set low for normal mode as data transceiver (Default is low with 10k to GND). Set high to put into sleep mode.



  // reserve 200 bytes for the inputString:
  // inputString.reserve(1000);
}

void loop() {
  /*
  The red LED flash when the module is transmitting, the red LED will be off when the transmission is finished.
The green LED is off when the module is waiting for data to be received, the green LED will flash once when the module receives data.
  */
  // print the string when a newline arrives:
  delay(1000);
  Serial2.write(Set_Reciver, sizeof(Set_Reciver));  //
  // Serial2.println();
  // Serial2.write(Set_Disturb, sizeof(Set_Disturb));  //

  /*
  if (stringComplete) {
    Serial.println(inputString);
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
*/

  if (Serial2.available()) {     // if date is coming from software serial port ==> data is coming from SoftSerial shield {
    while (Serial2.available())  // reading data into char array
    {
      buffer[count++] = Serial2.read();  // writing data into array
      if (count == 64) break;
    }
    for (int i = 0; i < count; i++) {
      Serial.print(buffer[i], HEX);  // if no data transmission ends, write buffer to hardware serial port
    }
    clearBufferArray();  // call clearBufferArray function to clear the stored data from the array
    count = 0;           // set counter of while loop to zero
  }



  if (Serial.available())          // if data is available on hardware serial port ==> data is coming from PC or notebook
    Serial2.write(Serial.read());  // write it to the SoftSerial shield
  Serial.println(">");

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

void clearBufferArray()  // function to clear buffer array
{
  for (int i = 0; i < count; i++) { buffer[i] = NULL; }  // clear all index of array with command NULL
}
