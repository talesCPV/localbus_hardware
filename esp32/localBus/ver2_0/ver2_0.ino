// Inclusão das bibliotecas
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <EEPROM.h>
#include <stdio.h>
#include <HTTPClient.h>

// AP Mode Credentials
const char* ssid_ap = "LocalBus_Conf";
char* pass_ap = "flexibus";
String token = "";

String params = "id_carro=2&placa=AAA0A00";
String apiEndpoint = "https://www.planet3.com.br/localbus/backend/esp/getToken.php";



// Instanciação do objeto da classe AsyncWebServer
AsyncWebServer server(80);