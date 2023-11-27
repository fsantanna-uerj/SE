#include <avr/io.h>

#define OVF (*((volatile  uint8_t*) 0x36))
#define PRE (*((volatile  uint8_t*) 0x81))
#define CNT (*((volatile uint16_t*) 0x84))

#define RED (*((volatile uint8_t*) 0x29))
#define CFG (*((volatile uint8_t*) 0x2A))
#define WRI (*((volatile uint8_t*) 0x2B))

typedef enum {
  FECHADO, ABERTO, ERRO, N_ESTADOS
} ESTADO;

typedef enum {
  PAGTO, ACESSO, N_EVENTOS
} EVENTO;

ESTADO TRANSICAO[N_ESTADOS][N_EVENTOS] = {
  // PAGTO, ACESSO
  ABERTO, ERRO,     // FECHADO
  ERRO,   FECHADO,  // ABERTO
  ERRO,   ERRO      // ERRO
};

void efeito (ESTADO s) {
  switch (s) {
    case FECHADO:
      CFG = 0b11111111;
      WRI = 0;
      WRI &= 0b11111101; // desliga o LED
      break;
    case ABERTO:
      CFG = 0b11111111;
      WRI = 0;
      WRI |= 0b00000010; // liga o LED
      break;
    case ERRO:
      PRE = 0b00000101;
      while (1) {
        CNT = 0xC000;       // 1s
        WRI ^= 0b00000010;  // alterna LED
        while((OVF & 0b00000001) == 0);
        OVF = 0b00000001;
      }
  }
}

EVENTO polling () {
  while (1) {
    if (RED & 0b00001000) { // BOTAO_P
      while (RED & 0b00001000);
      delayMicroseconds(1000);
      return PAGTO;
    }
    if (RED & 0b00010000) { // BOTAO_A
      while (RED & 0b00010000);
      delayMicroseconds(1000);
      return ACESSO;
    }
  }
}

int main (void) {
  CFG = 0b00000010;    // LED[1]=saída, botões[3,4]=entrada
  ESTADO s = FECHADO;

  while (1) {
    efeito(s);
    EVENTO e = polling();
    s = TRANSICAO[s][e];
  }
}