void connect(String ssid, String pass){
  WiFi.begin(ssid, pass);
  Serial.print("Conectando na rede WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Rede WiFi conectada com sucesso! Seu IP -> ");
  Serial.println(WiFi.localIP());
}