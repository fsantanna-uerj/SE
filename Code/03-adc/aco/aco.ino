void setup() {
  ACSR  = 0;
  pinMode(13, OUTPUT);
}

void loop() {
  int aco = ACSR;
  aco &= (1 << ACO);
  digitalWrite(13, aco);
}
