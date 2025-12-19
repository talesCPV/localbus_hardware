

void setup() {
  Serial.begin(115200);
  Serial.println();
  pinMode(2, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
}

// the loop function runs over and over again forever
void loop() {
  led(2,0);
//  digitalWrite(2, LOW);   // Turn the LED on (Note that LOW is the voltage level
  // but actually the LED is on; this is because
  // it is active low on the ESP-01)
  Serial.print("OFF");
  delay(timer);                      // Wait for a second
//  digitalWrite(2, HIGH);  // Turn the LED off by making the voltage HIGH
  led(2,1);

  Serial.println("- ON");
  delay(timer);                      // Wait for two seconds (to demonstrate the active low LED)

}