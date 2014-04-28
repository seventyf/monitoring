//----------------------------------------------
// coursework p00602 2012
// Peter Haban
// master node/data concentrator
// version 1.0 - coursework demonstration
//----------------------------------------------

#include <XBee.h>
#include <SPI.h>
#include <Ethernet.h>
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(10,0,0,60);

EthernetServer server(80);

XBee xbee = XBee();
ZBRxResponse zbRx = ZBRxResponse();
uint8_t text[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //initialises the data array with 0s

//local variables to submit the readings from the payload to the php form
float A = 0;
float B = 0;
float C = 0;
int D = 0;
int E = 0;
int F = 0;
int G = 0;


void setup () {
  delay(1000);
  Serial.begin(9600);
  xbee.setSerial(Serial);
  Ethernet.begin(mac, ip);
  server.begin();
 // Serial.print("server is at ");
 // Serial.println(Ethernet.localIP());
}

void loop () {

 

 EthernetClient client = server.available();
  if (client) {
   // Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
      //  Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
      client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          // output the value of each analog input pin
         
            client.println("analog input ");
           client.println(A);
           client.println(B);
           client.println(C);
           client.println(D);
           client.println(E);
           client.println(F);
           
          
                
          
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
  //  Serial.println("client disconnected");
  }
  
   // read any data that is available:
  xbee.readPacket();

  // check if a packet was received: 
  if (xbee.getResponse().isAvailable()) {
    if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
      xbee.getResponse().getZBRxResponse(zbRx);
    // read available message into text
     for (int i = 0; i < zbRx.getDataLength(); i++) {
         
          text [i] = zbRx.getData(i);
     }

     
     
D = text[0] ; //assigns the sensor readings to variables A-F which we can then send to the terminal and submit to the php form
E = text[1];
F = text[2] ;
A = D /100;
B=  E /100;
C = F /100;

 uint8_t analogHigh = text[0];
 uint8_t analogLow = text[1];
 int value1 = analogLow + (analogHigh * 256);
//Serial.println(flag);
    } 
  }
    }
  



