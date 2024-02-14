//Definicion de los pines de salida
int currentLED = 14;
int contador = 0;
int limite = 44;

void setup() {
  Serial.begin(115200); // Habilitación del puerto serial
  delay(500);
  for (int i = 14; i <= 22; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}

void loop() {
  int p0 = touchRead(T0);
  int p4 = touchRead(T4);
  delay(300);

  if (p0 <= limite) {
    if (contador <= 8) {
      digitalWrite(currentLED, HIGH);
      contador++;
      currentLED = currentLED + 1;
    }
  }

  if (p4 <= limite) {
    if (contador > 0) {
      currentLED = currentLED - 1;
      digitalWrite(currentLED, LOW);
      contador--;
    }
  }
}

