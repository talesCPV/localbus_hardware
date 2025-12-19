void setup() {
  Serial.begin(115200);
  // Conecta-se ao Ponto de acesso com as credenciais fornecidas
  connect(ssid, pass);

  router();

  server.begin();

  Serial.println(ler(0));
  Serial.println(ler(16));

}
void loop() {}


