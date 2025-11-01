// ============================================================

// === MINI SUMO - VERSIÓN AUSTERA CON PINES REALES ========

// === Evitación al inicio + prioridad: no salirse del ring ==

// ============================================================


// --- Pines de motores

#define PIN_MOTOR_LEFT_1 6

#define PIN_MOTOR_LEFT_2 5

#define PIN_MOTOR_RIGHT_1 11

#define PIN_MOTOR_RIGHT_2 10


// --- Pines de sensores de línea (QTR-1A)

#define QTR_LEFT A5

#define QTR_RIGHT A1

int count=0;

int L_LINE_REF_VALUE = 452;

int R_LINE_REF_VALUE = 444;

int start_module_status=0;


// --- Pines sensores JS40F (oponente)

#define PIN_START_MODULE 3


#define SENSOR_LEFT A4

#define SENSOR_MIDDLE A3

#define SENSOR_RIGHT A2


// --- LED indicador

#define LED_STATUS 13


// ============================================================

// SETUP

// ============================================================

void setup() {


Serial.begin(9600);


// Pines de motores

pinMode(PIN_MOTOR_LEFT_1, OUTPUT);

pinMode(PIN_MOTOR_LEFT_2, OUTPUT);

pinMode(PIN_MOTOR_RIGHT_1, OUTPUT);

pinMode(PIN_MOTOR_RIGHT_2, OUTPUT);


// Pines sensores

pinMode(PIN_START_MODULE,INPUT);

pinMode(QTR_LEFT, INPUT);

pinMode(QTR_RIGHT, INPUT);

pinMode(SENSOR_LEFT, INPUT);

pinMode(SENSOR_MIDDLE, INPUT);

pinMode(SENSOR_RIGHT, INPUT);


pinMode(LED_STATUS, OUTPUT);


// --- Movimiento inicial: retrocede y gira ---



attachInterrupt(digitalPinToInterrupt(PIN_START_MODULE), end_match, FALLING); // Interrupción que usaremos para detener el robot (control SONY y módulo de arranque).


while(start_module_status == 0){

start_module_status = digitalRead(PIN_START_MODULE);


}


}


// ============================================================

// LOOP PRINCIPAL

// ============================================================

void loop() {

if (count==0){

Serial.println("Mini Sumo inicializado... Secuencia evasiva");

delay(5000);

set_motors(-200, 200); // Gira hacia un lado

delay(200);

set_motors(-255, -255); // Reversa corta

delay(400);

stop_movement();

delay(100);

count=1;}


int qtrL = analogRead(QTR_LEFT);

int qtrR = analogRead(QTR_RIGHT);


bool irL = digitalRead(SENSOR_LEFT);

bool irC = digitalRead(SENSOR_MIDDLE);

bool irR = digitalRead(SENSOR_RIGHT);


// --- Actualizar LED de estado

if (irL || irC || irR || qtrL < L_LINE_REF_VALUE || qtrR < R_LINE_REF_VALUE) {

digitalWrite(LED_STATUS, HIGH);

} else {

digitalWrite(LED_STATUS, LOW);

}


// --- 1. Prioridad: no salirse del ring ---

if (qtrL < L_LINE_REF_VALUE || qtrR < R_LINE_REF_VALUE) {

Serial.println("⚠️ Línea detectada - Evadiendo");

set_motors(-255, -255); // Retrocede rápido

delay(400);

set_motors(-200, 200); // Gira para reubicarse

delay(400);

return;

}


// --- 2. Si detecta enemigo: ataque direccional ---

if (irL || irC || irR) {

if (irL && !irC && !irR) {

Serial.println("👈 Enemigo a la IZQUIERDA - girando antes de atacar");

set_motors(-200, 200); // Gira a la izquierda

delay(200); // Ajusta este delay para ~90°

}

else if (irR && !irC && !irL) {

Serial.println("👉 Enemigo a la DERECHA - girando antes de atacar");

set_motors(200, -200); // Gira a la derecha

delay(200); // Ajusta este delay para ~90°

}

else {

Serial.println("🎯 Enemigo al frente o múltiples sensores - ataque directo");

}


// Ataque frontal

set_motors(255, 255);

delay(200);

return;

}


// --- 3. Si no hay enemigo ni línea: patrulla ---

Serial.println("Buscando enemigo...");

set_motors(180, 150); // Avanza con ligera curva

delay(40);

}


// ============================================================

// FUNCIONES DE CONTROL DE MOTORES

// ============================================================

void stop_movement(void) {

digitalWrite(PIN_MOTOR_LEFT_1, HIGH);

digitalWrite(PIN_MOTOR_LEFT_2, HIGH);

digitalWrite(PIN_MOTOR_RIGHT_1, HIGH);

digitalWrite(PIN_MOTOR_RIGHT_2, HIGH);

}


void set_motors(int16_t l_motor_value, int16_t r_motor_value) {

// --- Motor Izquierdo

if (l_motor_value > 0) {

digitalWrite(PIN_MOTOR_LEFT_1, HIGH);

analogWrite(PIN_MOTOR_LEFT_2, 255 - l_motor_value);

} else {

digitalWrite(PIN_MOTOR_LEFT_2, HIGH);

analogWrite(PIN_MOTOR_LEFT_1, 255 + l_motor_value);

}


// --- Motor Derecho

if (r_motor_value > 0) {

digitalWrite(PIN_MOTOR_RIGHT_1, HIGH);

analogWrite(PIN_MOTOR_RIGHT_2, 255 - r_motor_value);

} else {

digitalWrite(PIN_MOTOR_RIGHT_2, HIGH);

analogWrite(PIN_MOTOR_RIGHT_1, 255 + r_motor_value);

}

}

void end_match(){

stop_movement();

while(1){

digitalWrite(LED_STATUS,HIGH);

}

}
