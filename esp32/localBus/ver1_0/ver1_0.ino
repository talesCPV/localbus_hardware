// Inclusão das bibliotecas
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <EEPROM.h>
#include <stdio.h>

// AP Mode Credentials
const char* ssid_ap = "LocalBus_Conf";
char* pass_ap = "flexibus";

// Instanciação do objeto da classe AsyncWebServer
AsyncWebServer server(80);
