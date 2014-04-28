//----------------------------------------------
// coursework p00602 2012
// Peter Haban
// node 0
// version 1.0 - coursework demonstration
//----------------------------------------------


#include <XBee.h>

// xbee
uint8_t text[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // this array will be used to transport data inbetween the XBees, id = 0
XBee xbee = XBee();
XBeeAddress64 remoteAddress = XBeeAddress64(0x0013a200, 0x40891DE1); // this is the network address of the XBee cordinator which is where we want this node to send it's data sets
ZBTxRequest zbTx = ZBTxRequest(remoteAddress, text, sizeof(text));

// analog sensors
int tmp102Address = 0x48; // hardware address for the I2C tmp102 sensor
int s_tempPin = 3; //analog pin for soil temperature reading
int s_tempReading = 12;
int temt6000Pin = 2; // analog pin for light level reading
int photocellReading=15;
int avg = 123 ;


// humidity
float val = 0;
float RH = 0;
int RH2 = 0;
float my_room_temperature = 20; //in degrees C, fall back to ensure loop won't get stuck in case we don't get a reading from the tmp102
float max_voltage = 3.27;
float Zerov = 0.8;
int celsius = 20;
int flag =0 ;
 
void setup(void) {
  Serial.begin(9600);
  xbee.setSerial(Serial);
 
}
 
void loop(void) {
 
  
  delay(100);              // wait 100ms for next reading  
  digitalWrite(13, HIGH);   // set the LED on
  delay(1000);              // wait for a second
  digitalWrite(13, LOW);    // set the LED off
  delay(1000);
  


 text[0] = s_tempReading >> 8 & 0xff;
 text[1] = s_tempReading & 0xff;
  

 text[2] = photocellReading >> 8 & 0xff;
 text[3] = photocellReading & 0xff;
 

 text[7] = avg >> 8 & 0xff;
 text[8] = avg & 0xff;
 

 
 // this simply fills the readings we acquired above into our XBee payload array
 text[4] = flag;
 text[5] = celsius;
 text[6] = RH2;
  
 

  
  xbee.send(zbTx); //this sends our XBee payload array to the coordinator
  delay(180000); //wait 3min before we acquire and send another set of sensor readings

  
}




