   
#include <WiFi.h>
#include <WebServer.h>
#include <EEPROM.h>

  
const char* ssid = "CASA_DA_VO_2G";
const char* password =  "12345678";




WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

    Serial.print("Conectando na rede WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Rede WiFi conectada com sucesso! Seu IP -> ");
  Serial.print(WiFi.localIP());
  
  server.begin();

  
  
}



void loop() {
  
  WiFiClient client = server.available();

    client.println(index_html);  



}