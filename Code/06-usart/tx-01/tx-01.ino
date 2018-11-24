#define BAUD (F_CPU/16/9600-1)

void setup (void) {
  /*Set baud rate */
  UBRR0H = BAUD >> 8;
  UBRR0L = BAUD;

  /* Enable transmitter */
  UCSR0B = 1 << TXEN0;   // TXEN="Transmitter Enable"
  
  /* Set frame format: 8data, 2stop bit */
  UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

char data = '0';
int  i    = 0;

void loop (void) {
  delay(1000);
  
  /* Wait for empty transmit buffer */
  while ( !( UCSR0A & (1<<UDRE0)) ) // UDRE="Data Register Empty"
    ;
    
  /* Put data into buffer, sends the data */
  UDR0 = data + i;                  // UDR="Data Register"
  i = (i + 1) % 10;
}

