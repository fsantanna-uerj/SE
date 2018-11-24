#define BAUD (F_CPU/16/9600-1)

void setup (void) {
  /*Set baud rate */
  UBRR0H = BAUD >> 8;
  UBRR0L = BAUD;

  /* Receive transmitter */
  UCSR0B = 1 << RXEN0;   // RXEN="Receiver Enable"
  
  /* Set frame format: 8data, 2stop bit */
  UCSR0C = (1<<USBS0)|(3<<UCSZ00);

  pinMode(13, OUTPUT);
}

void loop (void) {
  /* Wait for data to be received */
  while ( !(UCSR0A & (1<<RXC0)) )
    ;

  unsigned char data = UDR0;
  digitalWrite(13, data%2);
}

