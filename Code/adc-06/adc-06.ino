void setup() {
  Serial.begin(9600);
  
  ADMUX   = 0;                  // usa o canal 0
  ADMUX  |= (1 << REFS0);       // usa Vcc como referencia
  ADCSRA |= (1 << ADEN);        // habilita o ADC
}

void loop() {
  delay(1000);
  
  ADCSRA |= (1 << ADSC);        // inicia a conversao
  while(ADCSRA & (1 << ADSC));  // espera a conversao

  int v = ADCL;                 // tem que ser lido antes do ADCH
  v = (ADCH << 8) + v;          // valor de 2 bytes
  
  Serial.println(v);
}
