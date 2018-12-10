#define BAUD (F_CPU/16/9600-1)
#define BUF 32

unsigned char rx[BUF];
int rx_0 = 0;
int rx_n = 0;

unsigned char tx[BUF];
int tx_0 = 0;
int tx_n = 0;
int tx_ing = 0;

void setup (void) {
  UBRR0H = BAUD >> 8;
  UBRR0L = BAUD;
  UCSR0B = (1<<RXEN0)  | (1<<TXEN0) |
           (1<<RXCIE0) | (1<<TXCIE0); // enable interrupts
  UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void loop (void) {
  unsigned char data;
  int todo = 0;
  cli();
    if (rx_0 != rx_n) {
      todo = 1;
      data = rx[rx_0];
      rx_0 = (rx_0 + 1) % BUF;
    }
  sei();

  if (todo) {
    //delay(100);
    data = data + ('A' - 'a');
    cli();
      if (!tx_ing) {
        UDR0 = data;
        tx_ing = 1;
      } else {
        tx[tx_n] = data;
        tx_n = (tx_n + 1) % BUF;
      }
    sei();
  }
}

ISR (USART0_RX_vect) {
  rx[rx_n] = UDR0;
  rx_n = (rx_n + 1) % BUF;
}

ISR (USART0_TX_vect) {
  if (tx_0 != tx_n) {
    UDR0 = tx[tx_0];
    tx_0 = (tx_0 + 1) % BUF;
    tx_ing = 1;
  } else {
    tx_ing = 0;
  }
}

