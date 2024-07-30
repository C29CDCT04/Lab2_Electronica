# Lab2_Electronica
/* Universidad del Valle de Guatemala
Facultad de Ingeniería
Departamento de Electrónica, Mecatrónica y Biomédica
Electrónica Digital 2

Carlos Daniel Camacho Tista - 22690
Susan Daniela Guevara Catalán - 22519

Contador con dos modos: décadas y binario hecho con leds */

// Librerías
#include <stdint.h>
#include <stdbool.h>

// Definiciones de pines
#define L1 23
#define L2 22
#define L3 21
#define L4 19
#define Modo 4
#define Aum 5
#define Dis 15

// Variables globales
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
    digitalWrite(L1, LOW);
    digitalWrite(L2, LOW);
    digitalWrite(L3, LOW);
    digitalWrite(L4, LOW);
    pinMode(Modo, INPUT_PULLDOWN);
    pinMode(Aum, INPUT_PULLUP);
    pinMode(Dis, INPUT);
}

// Loop principal
void loop() {
    int m = modo(digitalRead(Modo));

    if (m == 0) {
        // Contador en modo decena
        b1_state = digitalRead(Aum);
        if (b1_state != last_b1_state) {
            if (b1_state == 0) {
                if (count == 0) {
                    digitalWrite(L1, LOW);
                    digitalWrite(L2, LOW);
                    digitalWrite(L3, LOW);
                    digitalWrite(L4, LOW);
                    count2 = count + 4;
                }
                if (count == 1) {
                    digitalWrite(L1, HIGH);
                    digitalWrite(L2, LOW);
                    digitalWrite(L3, LOW);
                    digitalWrite(L4, LOW);
                    count2 = count - 1;
                }
                if (count == 2) {
                    digitalWrite(L1, LOW);
                    digitalWrite(L2, HIGH);
                    digitalWrite(L3, LOW);
                    digitalWrite(L4, LOW);
                    count2 = count - 1;
                }
                if (count == 3) {
                    digitalWrite(L1, LOW);
                    digitalWrite(L2, LOW);
                    digitalWrite(L3, HIGH);
                    digitalWrite(L4, LOW);
                    count2 = count - 1;
                }
                if (count == 4) {
                    digitalWrite(L1, LOW);
                    digitalWrite(L2, LOW);
                    digitalWrite(L3, LOW);
                    digitalWrite(L4, HIGH);
                    count = 0;
                    count2 = count - 1;
                } else {
                    count++;
                }
            }
            delay(200);
            last_b1_state = b1_state;
        }

        b2_state = digitalRead(Dis);
        if (b2_state != last_b2_state) {
            if (b2_state == 1) {
                if (count2 == 1) {
                    digitalWrite(L1, HIGH);
                    digitalWrite(L2, LOW);
                    digitalWrite(L3, LOW);
                    digitalWrite(L4, LOW);
                    count = count2 + 1;
                }
                if (count2 == 2) {
                    digitalWrite(L1, LOW);
                    digitalWrite(L2, HIGH);
                    digitalWrite(L3, LOW);
                    digitalWrite(L4, LOW);
                    count = count2 + 1;
                }
                if (count2 == 3) {
                    digitalWrite(L1, LOW);
                    digitalWrite(L2, LOW);
                    digitalWrite(L3, HIGH);
                    digitalWrite(L4, LOW);
                    count = count2 + 1;
                }
                if (count2 == 4) {
                    digitalWrite(L1, LOW);
                    digitalWrite(L2, LOW);
                    digitalWrite(L3, LOW);
                    digitalWrite(L4, HIGH);
                    count = count2 - 4;
                }
                if (count2 == 0) {
                    digitalWrite(L1, LOW);
                    digitalWrite(L2, LOW);
                    digitalWrite(L3, LOW);
                    digitalWrite(L4, LOW);
                    count2 = 4;
                    count = count2 + 1;
                } else {
                    count2--;
                }
            }
            delay(200);
            last_b2_state = b2_state;
        }
    } else {
        // Contador en modo binario
        b1_state = digitalRead(Aum);
        if (b1_state != last_b1_state) {
            if (b1_state == 0) {
                count = (count + 1) % 16;
                mostrarBinario(count);
                delay(200);
            }
            last_b1_state = b1_state;
        }

        b2_state = digitalRead(Dis);
        if (b2_state != last_b2_state) {
            if (b2_state == 1) {
                count = (count - 1) % 16;
                mostrarBinario(count);
                delay(200);
            }
            last_b2_state = b2_state;
        }
    }
}

void mostrarBinario(uint8_t numero) {
    digitalWrite(L1, numero & 0x01);
    digitalWrite(L2, (numero >> 1) & 0x01);
    digitalWrite(L3, (numero >> 2) & 0x01);
    digitalWrite(L4, (numero >> 3) & 0x01);
}

int modo(int x) {
    if (x == 0) {
        return 0;
    } else {
        return 1;
    }
}
