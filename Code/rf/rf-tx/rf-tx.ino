#include <VirtualWire.h>
 
void setup() {
  Serial.begin(9600);
  vw_set_tx_pin(8);
  vw_setup(2000);   // BPS
}

uint8_t v = 0;

void loop()
{
  vw_send(&v, 1);
  vw_wait_tx();
  Serial.println(v);
  v++;
  delay(250);
}
