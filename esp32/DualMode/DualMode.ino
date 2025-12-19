// Inclusão das bibliotecas
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <EEPROM.h>

// Station Mode Credentials
const char* ssid_sta = "CASA_DA_VO_2G";
const char* password_sta = "12345678";

// AP Mode Credentials
const char* ssid_ap = "ESP32_AP";
const char* password_ap = "12345678";

// Instanciação do objeto da classe AsyncWebServer
AsyncWebServer server(80);
