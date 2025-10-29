/*
  🥋 Mini Sumo Dojo – Día 2
  Calibración automática de sensores QTR-1A
*/

#define QTR_LEFT  A0
#define QTR_RIGHT A3

int ref_left = 0, ref_right = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("=== Calibración automática QTR-1A ===");
  long sumL = 0, sumR = 0;

  // Lecturas en superficie negra
  Serial.println("Coloca el robot sobre el área negra...");
  delay(3000);
  for (int i = 0; i < 50; i++) {
    sumL += analogRead(QTR_LEFT);
    sumR += analogRead(QTR_RIGHT);
    delay(50);
  }
  ref_left  = sumL / 50;
  ref_right = sumR / 50;

  Serial.print("Promedio negro: "); 
  Serial.print(ref_left); Serial.print(", "); Serial.println(ref_right);

  // Lecturas en línea blanca
  sumL = 0; sumR = 0;
  Serial.println("Ahora sobre la línea blanca...");
  delay(3000);
  for (int i = 0; i < 50; i++) {
    sumL += analogRead(QTR_LEFT);
    sumR += analogRead(QTR_RIGHT);
    delay(50);
  }
  int white_left  = sumL / 50;
  int white_right = sumR / 50;

  int umbralL = (ref_left + white_left) / 2;
  int umbralR = (ref_right + white_right) / 2;

  Serial.println("=== Umbrales sugeridos ===");
  Serial.print("Izquierdo: "); Serial.println(umbralL);
  Serial.print("Derecho : "); Serial.println(umbralR);
}

void loop() {}
      
