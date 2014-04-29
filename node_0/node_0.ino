//----------------------------------------------
// coursework p00602 2012
// Peter Haban
// node 0
// version 1.0 - coursework demonstration
//----------------------------------------------


#include <XBee.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// xbee
uint8_t text[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // this array will be used to transport data inbetween the XBees, id = 0
XBee xbee = XBee();
XBeeAddress64 remoteAddress = XBeeAddress64(0x0013a200, 0x40891DE1); // this is the network address of the XBee cordinator which is where we want this node to send it's data sets
ZBTxRequest zbTx = ZBTxRequest(remoteAddress, text, sizeof(text));


// Data wire is plugged into pin 3 on the Arduino
#define ONE_WIRE_BUS 3

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// Assign the addresses of your 1-Wire temp sensors.
// See the tutorial on how to obtain these addresses:
// http://www.hacktronics.com/Tutorials/arduino-1-wire-address-finder.html

DeviceAddress T1 = { 0x28, 0x84, 0x63, 0xD0, 0x4, 0x0, 0x0, 0xE8 };
DeviceAddress T2 = { 0x28, 0x56, 0x53, 0xD0, 0x4, 0x0, 0x0, 0xC6 };
DeviceAddress T3 = { 0x28, 0x37, 0x90, 0xD0, 0x04, 0x00, 0x00, 0x5E };
 
int T1_S = 0;
int T2_S = 0;
int T3_S = 0;
float T1_R = 0;
float T2_R = 0;
float T3_R = 0;
 
void setup(void) {
  Serial.begin(9600);
  xbee.setSerial(Serial);
   // Start up the library
  sensors.begin();
  // set the resolution to 10 bit (good enough?)
  sensors.setResolution(T1, 10);
  sensors.setResolution(T2, 10);
  sensors.setResolution(T3, 10);
}
 
void loop(void) {
 
  
  delay(100);              // wait 100ms for next reading  
  digitalWrite(13, HIGH);   // set the LED on
  delay(1000);              // wait for a second
  digitalWrite(13, LOW);    // set the LED off
  delay(1000);
sensors.requestTemperatures();  
T1_R = sensors.getTempC(T1);
T2_R = sensors.getTempC(T2);
T3_R = sensors.getTempC(T3);

T1_S = T1_R *100;
T2_S = T2_R *100;
T3_S = T3_R *100;
 text[0] = T1_S >> 8 & 0xff;
 text[1] = T1_S & 0xff;
 text[2] = T2_S >> 8 & 0xff;
 text[3] = T2_S & 0xff;
 text[4] = T3_S >> 8 & 0xff;
 text[5] = T3_S & 0xff;
 text[6] = 3;
 text[7] = 4;
 text[8] = 5;
 text[9] = 6;
 
 

  
  xbee.send(zbTx); //this sends our XBee payload array to the coordinator
  delay(3000); //wait 3min before we acquire and send another set of sensor readings

  
}




