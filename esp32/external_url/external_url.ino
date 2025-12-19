// Inclusão das bibliotecas
#include <WiFi.h>
#include <HTTPClient.h>

char* ssid = "CASA_DA_VO_2G";
char* pass = "12345678";

String params = "id_carro=2&placa=AAA0A00";
String apiEndpoint = "https://www.planet3.com.br/localbus/backend/esp/getToken.php";