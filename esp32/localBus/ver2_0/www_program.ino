void setup() {

  pinMode(2, OUTPUT); // Initialize the LED_BUILTIN pin as an output

  Serial.begin(115200);
  connect();
  router();

//  Serial.println(curl_GET(apiEndpoint));
//  Serial.println(curl_POST(apiEndpoint,params));
  startDevice();

  Serial.println(WiFi.macAddress());

}

void loop(){}