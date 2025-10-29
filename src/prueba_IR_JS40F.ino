/*
  🥋 Mini Sumo Dojo – Día 2
  Prueba de detección del oponente con JS40F (sensor IR digital)
*/

#define SENSOR_LEFT   A4
#define SENSOR_MIDDLE A5
#define SENSOR_RIGHT  2
#define LED_STATUS    13

void setup() {
  Serial.begin(9600);
  pinMode(SENSOR_LEFT, INPUT);
  pinMode(SENSOR_MIDDLE, INPUT);
  pinMode(SENSOR_RIGHT, INPUT);
  pinMode(LED_STATUS, OUTPUT);
  Serial.println("=== Prueba Sensor JS40F (IR Digital) ===");
}

void loop() {
  bool left   = digitalRead(SENSOR_LEFT);
  bool middle = digitalRead(SENSOR_MIDDLE);
  bool right  = digitalRead(SENSOR_RIGHT);

  Serial.print("Izq: "); Serial.print(left);
  Serial.print("  Cen: "); Serial.print(middle);
  Serial.print("  Der: "); Serial.println(right);

  // Enciende el LED si se detecta oponente
  if (left || middle || right) digitalWrite(LED_STATUS, HIGH);
  else digitalWrite(LED_STATUS, LOW);

  delay(200);
}
      
