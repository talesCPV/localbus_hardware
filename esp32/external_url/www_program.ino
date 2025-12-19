void setup() {
  Serial.begin(115200);
  // Conecta-se ao Ponto de acesso com as credenciais fornecidas
  connect(ssid, pass);

  Serial.println(curl_POST(apiEndpoint,params));

}
void loop() {}