void setup() {
  Serial.begin(9600);
}

void loop() {
  delay(1000);
  int v = analogRead(A0);
  Serial.println(v);
}
