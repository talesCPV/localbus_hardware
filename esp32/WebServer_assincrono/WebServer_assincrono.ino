
// Inclusão das bibliotecas
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <EEPROM.h>

// Instanciação do objeto da classe AsyncWebServer
AsyncWebServer server(80);
// Constantes das credenciais do WiFi
char* ssid = "CASA_DA_VO_2G";
char* pass = "12345678";
