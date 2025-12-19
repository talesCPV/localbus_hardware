#include <TinyGPSPlus.h>

// Define the RX and TX pins for Serial 2
#define RXD2 16
#define TXD2 17

#define GPS_BAUD 115200

TinyGPSPlus gps;

// Create an instance of the HardwareSerial class for Serial 2
HardwareSerial gpsSerial(2);

void setup(){
  // Serial Monitor
  Serial.begin(115200);
  
  // Start Serial 2 with the defined RX and TX pins and a baud rate of 9600
  gpsSerial.begin(GPS_BAUD, SERIAL_8N1, RXD2, TXD2);
  Serial.println("Serial 2 started at 9600 baud rate");
}

void loop(){
  while (gpsSerial.available() > 0){
    // get the byte data from the GPS
//    char gpsData = gpsSerial.read();
//    Serial.print(gpsData);
    if (gps.encode(gpsSerial.read())) {
      // If a complete and valid GPS message (sentence) has been processed
      if (gps.location.isValid()) {
        // Print the latitude and longitude in decimal format with 6 decimal places
        Serial.print("Latitude: ");
        Serial.println(gps.location.lat(), 6);
        Serial.print("Longitude: ");
        Serial.println(gps.location.lng(), 6);
      }else{
        Serial.print("*");
      }
    }
  }
  delay(2000);
  Serial.print(".");
}