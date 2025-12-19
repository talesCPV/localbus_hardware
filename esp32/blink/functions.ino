void led(int prt, int state){
  digitalWrite(prt, state? HIGH : LOW);  // Turn the LED off by making the voltage HIGH
}