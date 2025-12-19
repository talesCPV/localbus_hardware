// Inclusão das bibliotecas
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <EEPROM.h>


// Instanciação do objeto da classe AsyncWebServer
AsyncWebServer server(80);

// Replace with your network credentials
const char* ssid = "LocalBus_Server";
const char* pass = "12345678";


