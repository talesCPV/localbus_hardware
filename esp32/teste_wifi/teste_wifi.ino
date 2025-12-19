#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <HTTPClient.h>

  const WiFiClient client; // Declare the client object
  const String params = "id_carro=1&placa=AAA0A00";
  const String apiEndpoint = "https://www.planet3.com.br/localbus/backend/esp/getToken.php";
 
  const char* ssid = "KIKAETALES";
  const char* pass = "rafael23";

  AsyncWebServer server(80);

void setIP(){

  // Set IPs conf.
  
    IPAddress staticIP(192, 168, 1, 100);
    IPAddress gateway(192, 168, 1, 1);
    IPAddress subnet(255, 255, 255, 0);
    IPAddress primaryDNS(1,1,1,1); // Cloudflare DNS or your router's IP
    IPAddress secondaryDNS(1,0,0,1);


  // --- Set Static IP ---
  WiFi.config(staticIP, gateway, subnet, primaryDNS, secondaryDNS);
  Serial.print("Novo IP Estático: ");
  Serial.println(WiFi.localIP());
}

void connect(){
    // Start the ESP32 in Station Mode
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);
    Serial.print("Connecting to Wi-Fi...");

    int i=30;
    // Wait for the connection to establish
    while (WiFi.status() != WL_CONNECTED && i>0) {
      delay(500);
      digitalWrite(2, i%2? HIGH : LOW);
      Serial.print(".");
      i--;
    }

    Serial.println();
    digitalWrite(2,HIGH);
    Serial.println("Connected to Wi-Fi!");
    Serial.println(WiFi.localIP()); // Should show your static IP now
    //setIP();
}

String curl_POST(String url, String params){  
  String payload = "";
  int httpResponseCode = 0;
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    http.begin(url);
    http.setFollowRedirects(HTTPC_FORCE_FOLLOW_REDIRECTS);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpResponseCode = http.POST(params);
    if (httpResponseCode > 0) {
      payload = http.getString();
    }
    http.end();
  }
  String out = "{\"code\":"+String(httpResponseCode)+",\"payload\":"+payload+"}";
  return out;
}

void router(){

  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    Serial.println();
    Serial.print("Acessando a rota / ");
    request->send(200, "text/plain", "HELLO ESP!");
  });

  server.on("/api", HTTP_GET, [](AsyncWebServerRequest * request) {
    Serial.println();
    Serial.print("Acessando a rota /api ");
    request->send(200, "text/plain", curl_POST(apiEndpoint,params));
  });

  server.begin();

}

void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT); // Initialize the LED_BUILTIN pin as an output
  connect();
  router();
  Serial.println(curl_POST(apiEndpoint,params));
}

void loop() {}