/*
  🥋 Mini Sumo Dojo – Día 2
  Prueba y calibración del sensor QTR-1A (reflectancia analógica)
*/

#define QTR_LEFT  A0
#define QTR_RIGHT A3

int left_value, right_value;

void setup() {
  Serial.begin(9600);
  Serial.println("=== Prueba Sensor QTR-1A (Línea) ===");
}

void loop() {
  left_value  = analogRead(QTR_LEFT);
  right_value = analogRead(QTR_RIGHT);

  Serial.print("Izq: "); Serial.print(left_value);
  Serial.print("  Der: "); Serial.println(right_value);
  delay(200);
}
