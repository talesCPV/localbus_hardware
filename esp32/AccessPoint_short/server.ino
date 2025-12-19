void connect(String ssid, String pass){

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, pass);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
}

void router(){


  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    Serial.println();
    Serial.print("Acessando a rota / ");

    request->send(200, "text/html", html);
  });

}



