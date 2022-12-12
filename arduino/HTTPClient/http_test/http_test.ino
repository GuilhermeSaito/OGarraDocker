int pinESP = 0;

void setup() {
  pinMode(pinESP, OUTPUT);
}

void loop() {
  digitalWrite(pinESP, LOW);

  delay(1000);
  digitalWrite(pinESP, HIGH);
  delay(1000);
}