#include <VirtualWire.h>
 
void setup()   {
  Serial.begin(9600);
  vw_set_rx_pin(5);
  vw_setup(2000);   // BPS
  vw_rx_start();
}
 
void loop()
{
  uint8_t v;
  uint8_t n = 1;
  if (vw_get_message(&v, &n)) {
    Serial.println(v);
  }
}
