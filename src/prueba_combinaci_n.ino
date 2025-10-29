/*
  🥋 Mini Sumo Dojo – Día 2
  Lectura combinada de sensores IR (JS40F) y línea (QTR-1A)
*/

#define SENSOR_LEFT   A4
#define SENSOR_MIDDLE A5
#define SENSOR_RIGHT  2
#define QTR_LEFT      A0
#define QTR_RIGHT     A3
#define LED_STATUS    13

void setup() {
  Serial.begin(9600);
  pinMode(SENSOR_LEFT, INPUT);
  pinMode(SENSOR_MIDDLE, INPUT);
  pinMode(SENSOR_RIGHT, INPUT);
  pinMode(LED_STATUS, OUTPUT);
  Serial.println("=== Lectura combinada IR + Línea ===");
}

void loop() {
  // Sensores IR (digital)
  bool irL = digitalRead(SENSOR_LEFT);
  bool irC = digitalRead(SENSOR_MIDDLE);
  bool irR = digitalRead(SENSOR_RIGHT);

  // Sensores de línea (analógico)
  int qtrL = analogRead(QTR_LEFT);
  int qtrR = analogRead(QTR_RIGHT);

  Serial.print("IR [L,C,R]: ");
  Serial.print(irL); Serial.print(", ");
  Serial.print(irC); Serial.print(", ");
  Serial.print(irR);
  Serial.print(" | Línea [L,R]: ");
  Serial.print(qtrL); Serial.print(", ");
  Serial.println(qtrR);

  // LED encendido si hay detección de oponente o borde
  if (irL || irC || irR || qtrL < 400 || qtrR < 400)
    digitalWrite(LED_STATUS, HIGH);
  else
    digitalWrite(LED_STATUS, LOW);

  delay(250);
}
      
