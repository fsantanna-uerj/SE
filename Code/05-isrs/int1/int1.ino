void setup() {
  pinMode( 2, INPUT_PULLUP);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  EICRA = (1 << ISC10) | (0 << ISC11);
  EIMSK = (1 << INT1);  
}

void loop () {
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
}
  
ISR(INT1_vect) {
  digitalWrite(12, digitalRead(2));
}

