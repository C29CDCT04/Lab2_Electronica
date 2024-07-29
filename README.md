# Lab2_Electronica
/* Universidad del Valle de Guatemala
Facultad de Ingeniería
Departamento de Electrónica, Mecatrónica y Biomédica
Electrónica Digital 2

Carlos Daniel Camacho Tista - 22690
Susan Daniela Guevara Catalán - 22519

Contador con dos modos: décadas y binario hecho con leds */

// Librerías
#include <Arduino.h>

// Variables globales
#define L1 23
#define L2 22
#define L3 21
#define L4 19
#define Modo 4
#define Aum 5
#define Dis 15
uint8_t b1_state = 1;
uint8_t last_b1_state = 1;
uint8_t b2_state = 0;
uint8_t last_b2_state = 0;
uint8_t count = 1;
uint8_t count2 = 4;

// Prototipos de funciones
int modo(int);
void mostrarBinario(uint8_t numero);

// Función de configuración
void setup() {
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);
  pinMode(L4, OUTPUT);
  digitalWrite(L1,LOW);
  digitalWrite(L2,LOW);
  digitalWrite(L3,LOW);
  pinMode(Modo,INPUT_PULLDOWN);
  pinMode(Aun,INPUT_PULLUP);
  pinMode(Dis,INPUT);
}

// Loop principal
void loop() {

  // Lee el botón de modo, LOW es decena, HIGH es binario
  int m = modo(digitalRead(Modo));
  
  // Contador en modo decena
  if (m==0) {
    // Lee el botón más para incrementar la cuenta
    b1_state = digitalRead(Aum);
    // Verifica si el botón cambio de estado
    if (b1_state != last_b1_state) {
        // Verifica si presionaron el botón 
        if (b1_state == 0) {
          // Muestra el valor actual en las leds
          if (count == 0) {
            digitalWrite(L1,LOW);
            digitalWrite(L2,LOW);
            digitalWrite(L3,LOW);
            digitalWrite(L4,LOW);
            count2 = count+4;
          }
          if (count == 1) {
            digitalWrite(L1,HIGH);
            digitalWrite(L2,LOW);
            digitalWrite(L3,LOW);
            digitalWrite(L4,LOW);
            count2 = count-1;
          }
          if (count == 2) {
            digitalWrite(L1,LOW);
            digitalWrite(L2,HIGH);
            digitalWrite(L3,LOW);
            digitalWrite(L4,LOW);
            count2 = count-1;
          }
          if (count == 3) {
            digitalWrite(L1,LOW);
            digitalWrite(L2,LOW);
            digitalWrite(L3,HIGH);
            digitalWrite(L4,LOW);
            count2 = count-1;
          }
          // Incrementar el contador y reiniciar a 0 si está en F = 15
          if (count == 4) {
            digitalWrite(L1,LOW);
            digitalWrite(L2,LOW);
            digitalWrite(L3,LOW);
            digitalWrite(L4,HIGH);
            count = 0;
            count2 = count-1;
          } else {
            count++;
          }
        }
        // Esperar un momento para evitar el rebote del botón
        delay(200);
        last_b1_state = b1_state;
      } 
        

    // Lee el botón menos para disminuir la cuenta
    b2_state = digitalRead(Dis);
    // Verificar si el botón ha cambiado de estado
    if (b2_state != last_b2_state) {
        // Verificar si el botón ha sido presionado 
        if (b2_state == 1) {
          // Mostrar el valor actual en las leds
          if (count2 == 1) {
            digitalWrite(L1,HIGH);
            digitalWrite(L2,LOW);
            digitalWrite(L3,LOW);
            digitalWrite(L4,LOW);
            count = count2+1;
          }
          if (count2 == 2) {
            digitalWrite(L1,LOW);
            digitalWrite(L2,HIGH);
            digitalWrite(L3,LOW);
            digitalWrite(L4,LOW);
            count = count2+1;
          }
          if (count2 == 3) {
            digitalWrite(L1,LOW);
            digitalWrite(L2,LOW);
            digitalWrite(L3,HIGH);
            digitalWrite(L4,LOW);
            count = count2+1;
          }
        
          if (count2 == 4) {
            digitalWrite(L1,LOW);
            digitalWrite(L2,LOW);
            digitalWrite(L3,LOW);
            digitalWrite(L4,HIGH);
            count = count2-4;
          }

          // Disminuir el contador y reiniciar a 4
          if (count2 == 0) {
            digitalWrite(L1,LOW);
            digitalWrite(L2,LOW);
            digitalWrite(L3,LOW);
            digitalWrite(L4,LOW);
            count2 = 4;
            count = count2+1;
          } else {
            count2--;
          }
        }
        // Esperar un momento para evitar el rebote del botón
        delay(200);
        last_b2_state = b2_state;
    }   
  }

  else {
    // Contador en modo binario
    // Lee el botón más para incrementar la cuenta
    b1_state = digitalRead(Aum);
    if (b1_state != last_b1_state) {
      if (b1_state == 0) {
        count = (count + 1) % 16; // Incrementa y vuelve a 0 después de 15
        mostrarBinario(count);
        delay(200);
      }
      last_b1_state = b1_state;
    }

    // Botón menos para disminuir la cuenta
    b2_state = digitalRead(Dis);
    if (b2_state != last_b2_state) {
      if (b2_state == 1) {
        count = (count - 1) % 16; // Decrementa y vuelve a 15 después de 0
        mostrarBinario(count);
        delay(200);
      }
      last_b2_state = b2_state;
    }
  }
}

// Muestra el número binario
void mostrarBinario(uint8_t numero) {
  digitalWrite(Led_1, numero & 0x01);
  digitalWrite(Led_2, (numero >> 1) & 0x01);
  digitalWrite(Led_3, (numero >> 2) & 0x01);
  digitalWrite(Led_4, (numero >> 3) & 0x01);
}

// Determina el modo
int modo(int x) {
  if (x == 0) {
    return 0;
  }
  else {
    return 1;
  }
}
