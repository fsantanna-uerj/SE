#define BAUD (F_CPU/16/9600-1)

void setup (void) {
  /*Set baud rate */
  UBRR0H = BAUD >> 8;
  UBRR0L = BAUD;

  /* Enable transmitter */
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);
  
  /* Set frame format: 8data, 2stop bit */
  UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void loop (void) {

  /* Wait for data to be received */
  while ( !(UCSR0A & (1<<RXC0)) )
    ;

  unsigned char data = UDR0;

  data = data + ('A' - 'a');
  //delay(1);
  
  /* Wait for empty transmit buffer */
  while ( !( UCSR0A & (1<<UDRE0)) ) // UDRE="Data Register Empty"
    ;
    
  /* Put data into buffer, sends the data */
  UDR0 = data;
}

