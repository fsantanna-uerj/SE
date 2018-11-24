#define BAUD (F_CPU/16/9600-1)

void setup (void) {
  /*Set baud rate */
  UBRR0H = BAUD >> 8;
  UBRR0L = BAUD;

  /* Enable receiver and transmitter */
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);
  
  /* Set frame format: 8data, 2stop bit */
  UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void loop (void) {
  delay(1000);
  
  /* Wait for empty transmit buffer */
  while ( !( UCSR0A & (1<<UDRE)) )
    ;
    
  /* Put data into buffer, sends the data */
  UDR0 = data;
}

