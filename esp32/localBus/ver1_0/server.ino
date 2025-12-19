bool connect(){

    const String ssid = ler(0);
    const String pass = ler(16);

    bool out = 0;

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

    if(WiFi.status() == WL_CONNECTED){
      out = 1;
      digitalWrite(2,LOW);
      Serial.println("Connected to Wi-Fi!");
      Serial.println(WiFi.localIP()); // Should show your static IP now
      setIP();
    }else{
      WiFi.mode(WIFI_AP);
      digitalWrite(2,HIGH);
      // Start the ESP32 in Access Point Mode
      WiFi.softAP(ssid_ap, pass_ap);
      Serial.print("AP IP Address: ");
      Serial.println(WiFi.softAPIP());
    }

  return out;
}

void setIP(){

  // Set IPs conf.
    IPAddress staticIP(ler_hex(32),ler_hex(33),ler_hex(34),ler_hex(35));
    IPAddress gateway(ler_hex(36),ler_hex(37),ler_hex(38),ler_hex(39));
    IPAddress subnet(ler_hex(40),ler_hex(41),ler_hex(42),ler_hex(43));
    IPAddress primaryDNS(ler_hex(44),ler_hex(45),ler_hex(46),ler_hex(47));
    IPAddress secondaryDNS(ler_hex(48),ler_hex(49),ler_hex(50),ler_hex(51));

  // --- Set Static IP ---
  WiFi.config(staticIP, gateway, subnet, primaryDNS, secondaryDNS);

  Serial.print("Novo IP Estático: ");
  Serial.println(WiFi.localIP()); // Should show your static IP now
}

void router(){

  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    Serial.println();
    Serial.print("Acessando a rota / ");
    request->send(200, "text/html", indexHTML);
  });

  server.on("/config", HTTP_GET, [](AsyncWebServerRequest * request) {
    Serial.println();
    Serial.print("Acessando a rota / ");
    request->send(200, "text/html", login);
  });

  server.on("/openlogin", HTTP_POST, [](AsyncWebServerRequest *request) {
    // Access request details
    String clientIp = request->client()->remoteIP().toString();
    Serial.print("Request from: ");
    Serial.println(clientIp);

    int params = request->params();

    for (int i = 0; i < params; i++) {

      String field = request->getParam(i)->name().c_str();
      String value = request->getParam(i)->value().c_str();

      if(field == "pass"){
        if(value == "spider" || value == ler(52)){
          request->send(200, "text/html", menu );
        }else{
          request->send(200, "text/html", login );
        }
      }
    }
  });

  server.on("/savessid", HTTP_POST, [](AsyncWebServerRequest *request) {
    // Access request details
    String clientIp = request->client()->remoteIP().toString();
    Serial.print("Request from: ");
    Serial.println(clientIp);

    int params = request->params();
    int save = 0;
    for (int i = 0; i < params; i++) {

      String field = request->getParam(i)->name().c_str();
      String value = request->getParam(i)->value().c_str();

      if(field == "ssid"){
        gravar(0,value);
        save=1;
      }

      if(field == "pass"){
        gravar(16,value);
        save=1;
      }
    }

    // Send a response
    request->send(200, "text/plain", "{\"save\":"+String(save)+"}" );
  });

  server.on("/saveip", HTTP_POST, [](AsyncWebServerRequest *request) {

    int params = request->params();
    int save=0;

    for (int i = 0; i < params; i++) {

      String field = request->getParam(i)->name().c_str();
      String value = request->getParam(i)->value().c_str();
      for(int i=0; i<4; i++){
        int adress = field == "ip" ? 32 : field == "getway" ? 36 :field == "subnet" ? 40 :field == "dns1" ? 44 :field == "dns2" ? 48 : 0;
        if(adress>=32){
          String hex = value.substring(i*2,i*2+2);
          gravar_hex(adress+i,hex);
          save=1;
        }
      }
    }

    request->send(200, "text/plain", "{\"save\":"+String(save)+"}" );
  });

  server.on("/saveseg", HTTP_POST, [](AsyncWebServerRequest *request) {
    int params = request->params();
    int save=0;
    for (int i = 0; i < params; i++) {
      String field = request->getParam(i)->name().c_str();
      String value = request->getParam(i)->value().c_str();
      if(field == "dispseg"){
        gravar(52,value);
        Serial.println(value);
        save=1;
      }
    }
    request->send(200, "text/plain", "{\"save\":"+String(save)+"}" );
  });

  server.on("/saveconfig", HTTP_POST, [](AsyncWebServerRequest *request) {
    int params = request->params();
    int save = 0;
    for (int i = 0; i < params; i++) {
      String field = request->getParam(i)->name().c_str();
      String value = request->getParam(i)->value().c_str();
      if(field == "url"){
        gravar(68,value);
        save = 1;
      }
      if(field == "pin"){
        gravar(148,value);
        save = 1;
      }
      if(field == "id_carro"){
        gravar(152,value);
        save = 1;
      }
      if(field == "placa"){
        gravar(156,value);
        save = 1;
      }         
      if(field == "token"){
        gravar(164,value);
      }      
    }
    request->send(200, "text/plain", "{\"save\":"+String(save)+"}");
  });

  server.on("/getnetdata", HTTP_POST, [](AsyncWebServerRequest *request) {

    String IP = String(ler_hex(32))+"."+String(ler_hex(33))+"."+String(ler_hex(34))+"."+String(ler_hex(35));
    String gtw = String(ler_hex(36))+"."+String(ler_hex(37))+"."+String(ler_hex(38))+"."+String(ler_hex(39));
    String subnet = String(ler_hex(40))+"."+String(ler_hex(41))+"."+String(ler_hex(42))+"."+String(ler_hex(43));
    String primaryDNS = String(ler_hex(44))+"."+String(ler_hex(45))+"."+String(ler_hex(46))+"."+String(ler_hex(47));
    String secondaryDNS = String(ler_hex(48))+"."+String(ler_hex(49))+"."+String(ler_hex(50))+"."+String(ler_hex(51));
    String json = "{\"ssid\":\""+ler(0)+"\",\"pass\":\""+ler(16)+"\",\"ip\":\""+IP+"\",\"getaway\":\""+gtw+"\",\"subnet\":\""+subnet+"\",\"primaryDNS\":\""+primaryDNS+"\",\"secondaryDNS\":\""+secondaryDNS+"\"}";

    request->send(200, "text/plain", json );
  });

  server.on("/getsysdata", HTTP_POST, [](AsyncWebServerRequest *request) {
    String json = "{\"url\":\""+ler(68)+"\",\"pin\":\""+ler(148)+"\",\"id_carro\":\""+ler(152)+"\",\"placa\":\""+ler(156)+"\",\"token\":\""+ler(164)+"\"}";
    request->send(200, "text/plain", json );
  });

  server.on("/opentab", HTTP_POST, [](AsyncWebServerRequest *request) {

    int params = request->params();
    
    for (int i = 0; i < params; i++) {

      String field = request->getParam(i)->name().c_str();
      String value = request->getParam(i)->value().c_str();

      if(field=="tab"){
        const char *html = value=="config" ? config : value=="rede" ? rede : seg;
        request->send(200, "text/html", html );
      }

    }

  });


    server.begin();

  }