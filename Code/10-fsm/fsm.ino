#define LED 13
#define BUT  2

///////////////////////////
// GLOBAIS
///////////////////////////

int ESTADO;
int T0;

///////////////////////////
// ESTADOS
///////////////////////////

void estado_1 (unsigned long agora) {
  digitalWrite(LED, LOW);  
  T0 = agora;
  ESTADO = 1;
}

void estado_2 (unsigned long agora) {
  digitalWrite(LED, HIGH);  
  T0 = agora;
  ESTADO = 2;
}

void estado_3 (void) {
  ESTADO = 3;
}

void estado_4 (void) {
  ESTADO = 4;
}

///////////////////////////
// SETUP
///////////////////////////

void setup() {
  pinMode(BUT, INPUT_PULLUP);
  estado_1(millis());   // estado inicial
}

///////////////////////////
// LOOP
///////////////////////////

void loop () {
  // tratamento das entradas
  unsigned long agora = millis();
  int but = digitalRead(BUT);

  // transicao entre estados
  switch (ESTADO) {
    case 1: {
      if (agora-T0 >= 1000) {
        estado_2(agora);
      } else if (!but) {
        estado_3();
      }
      break;
    }
    case 2: {
      if (agora-T0 >= 1000) {
        estado_1(agora);
      } else if (!but) {
        estado_4();
      }      
      break;
    }
  }
}
