void connect(String ssid, String pass){

  WiFi.begin(ssid, pass);
  Serial.print("Conectando na rede WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Rede WiFi conectada com sucesso! Seu IP -> ");
  Serial.print(WiFi.localIP());

}

void router(){


  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    Serial.println();
    Serial.print("Acessando a rota / ");

    request->send(200, "text/html", html);
  });

  server.on("/action", HTTP_POST, [](AsyncWebServerRequest *request) {
    // Access request details
    String clientIp = request->client()->remoteIP().toString();
    Serial.print("Request from: ");
    Serial.println(clientIp);

    int params = request->params();
    
    String _ssid = "";
    String _pass = "";
    String out = "{\"save\":0}";

    for (int i = 0; i < params; i++) {

      String field = request->getParam(i)->name().c_str();
      String value = request->getParam(i)->value().c_str();

      Serial.println(field+":"+value);
      if(field == "ssid"){
        gravar(0,value);
        out = "{\"save\":1}";
      }

      if(field == "pass"){
        gravar(16,value);
        out = "{\"save\":1}";
      }

      Serial.println(value);

    }

    // Send a response
    request->send(200, "text/plain", out );
  });

}


/*
  void openCORS(){
    AsyncWebServerResponse *response = server.request->beginResponse(200, "text/plain", "Hello from ESP32!");
    response->addHeader("Access-Control-Allow-Origin", "*");
    response->addHeader("Access-Control-Max-Age", "600");
    response->addHeader("Access-Control-Allow-Methods", "PUT,POST,GET,OPTIONS");
    response->addHeader("Access-Control-Allow-Headers", "*");
  }
*/
