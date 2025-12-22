// Definições de constantes
#define RXD2 16
#define TXD2 17

// Inclusão das bibliotecas
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <EEPROM.h>
#include <stdio.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include <TinyGPSPlus.h>


// AP Mode Credentials
const char* ssid_ap = "LocalBus_Conf";
char* pass_ap = "flexibus";
String token = "";

String params = "id_carro=2&placa=AAA0A00";
String apiEndpoint = "https://www.planet3.com.br/localbus/backend/esp/getToken.php";

bool serverCom = false;
JSONVar carData = {};

String lat = "0";
String lon = "0";

// Instanciação de objetos de classe
AsyncWebServer server(80);
TinyGPSPlus gps;