// BLE Beacon with HM10(CC2541) module
// Md. Kamruzzaman Tipu
// Contact: it.ktipu@gmail.com


#include <SoftwareSerial.h>
#define PIN_TX  10
#define PIN_RX  9


SoftwareSerial mySerial(PIN_TX, PIN_RX);
unsigned long lastMillis;

void setup(){
  Serial.begin(9600);
  delay(1000);
  mySerial.begin(9600);
  delay(1000);

  ///////////////////BLE///////////////
  sendATcommand("AT+RENEW", 2000); // AT+RENEW (Restores the factory defaults)
  sendATcommand("AT+RESET", 2000); // AT+RESET (Reboots the HM10)
  sendATcommand("AT", 2000);  // AT (AT Test)
  sendATcommand("AT+MARJ0x1000", 2000); // AT+MARJ0x1000 (Sets iBeacon Major Number to 0x1000 HEX converted to 4096 in DEC)
  sendATcommand("AT+MINO0x0007", 2000); // AT+MINO0x0007 (Sets iBeacon Minor Number to 0x1000 HEX converted to 4096 in DEC)
  
  // set UUID to  36996276-CB00-40A2-A81E-D7F95858CA7C
  sendATcommand("AT+IBE036996276", 2000); // Sets bytes 0-3 
  sendATcommand("AT+IBE1CB0040A2", 2000); // Sets bytes 4-7
  sendATcommand("AT+IBE2A81ED7F9", 2000); // Sets bytes 8-11
  sendATcommand("AT+IBE35858CA7C", 2000); // Sets bytes 12-15
  
  sendATcommand("AT+ADVI5", 2000);  // AT+ADVI5 (Sets advertising interval to 5 i.e. 546.25 milliseconds)
  sendATcommand("AT+NAMENybSys", 2000); // AT+NAMEiBeacon (Set HM-10 module name to iBeacon. Change it according to use)
  sendATcommand("AT+ADTY3", 2000);  // AT+ADTY3 (Sets HM10 non-connectable to save the power and no client can connect to module helps in saving more power) 
  sendATcommand("AT+IBEA1", 2000); // AT+IBEA1 (Enables iBeacon Mode on HM10)
  sendATcommand("AT+DELO2", 2000); // AT+DELO2 (Sets the iBeacon in Broadcast mode only to save power. The HM10 can broadcasts its presence and scans for other devices as it is a Bluetooth Transceiver)
  sendATcommand("AT+PWRM0", 2000); // AT+PWRM0 (Enables HM10 to auto sleep and reduce power consumption from 8 to 0.18 mA. The iBeacon will be always transmitting though)
  sendATcommand("AT+RESET", 2000); // (Reboots the HM10)

  
}

void loop(){

}

String sendATcommand(const char *toSend, unsigned long milliseconds) {
  String result;
  Serial.print("Sending: ");
  Serial.println(toSend);
  mySerial.println(toSend);
  unsigned long startTime = millis();
  Serial.print("Received: ");
  while (millis() - startTime < milliseconds) {
    if (mySerial.available()) {
      char c = mySerial.read();
      Serial.write(c);
      result += c;  // append to the result string
    }
  }
Serial.println();  // new line after timeout.
return result;
}
