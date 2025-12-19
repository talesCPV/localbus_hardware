void connect(){

      // Start serial communication
//    Serial.begin(115200);

    // Start the ESP32 in Station Mode
    WiFi.begin(ssid_sta, password_sta);
    Serial.println("Connecting to Wi-Fi...");

    // Wait for the connection to establish
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println();
    // Once connected, print the IP address of the ESP32 in STA mode
    Serial.println("Connected to Wi-Fi!");
    Serial.print("STA IP Address: ");
    Serial.println(WiFi.localIP());

    // Start the ESP32 in Access Point Mode
    WiFi.softAP(ssid_ap, password_ap);

    // Print the IP address of the ESP32 in AP mode
    Serial.print("AP IP Address: ");
    Serial.println(WiFi.softAPIP());

    Serial.print("Rede WiFi conectada com sucesso! Seu IP -> ");
    Serial.print(WiFi.localIP());
  
}

void router(){


  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    Serial.println();
    Serial.print("Acessando a rota / ");

    request->send(200, "text/html", html);
  });

  server.on("/ip", HTTP_GET, [](AsyncWebServerRequest * request) {
    Serial.println();
    Serial.println("Acessando a rota /IP ");
    Serial.print("Seu IP local é ");
    Serial.print(WiFi.localIP());
//    request->send(200, "text/plain", WiFi.localIP());
  });


}