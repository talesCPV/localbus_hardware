#include <WiFi.h>
#include <DNSServer.h>
#include <WebServer.h>

// Constants and global variables
const byte DNS_PORT = 53;
const int WEBSERVER_PORT = 80;

IPAddress apIP(192, 168, 4, 1);
IPAddress netMsk(255, 255, 255, 0);

DNSServer dnsServer;
WebServer server(WEBSERVER_PORT);

char ap_ssid[32];
String ap_password = "password123";

TaskHandle_t webServerTaskHandle = NULL;

// [Previous function implementations remain the same]

void setupAP() {
  uint8_t mac[6];
  WiFi.macAddress(mac);
  snprintf(ap_ssid, sizeof(ap_ssid), "esp_%02X%02X%02X%02X%02X%02X", 
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  
  WiFi.softAPConfig(apIP, apIP, netMsk);
  WiFi.softAP(ap_ssid, ap_password.c_str());
  
  // DNS Server setup
  dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer.start(DNS_PORT, "*", apIP);
}

void setup() {
  Serial.begin(115200);
  
  setupAP();
  
  xTaskCreatePinnedToCore(
    webServerTask,
    "WebServerTask",
    8192,
    NULL,
    1,
    &webServerTaskHandle,
    1
  );
}

void loop() {
  // Other tasks can run here
  delay(10);
}
