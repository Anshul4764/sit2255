void setup() {
  pinMode(2, OUTPUT);
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop() {
  if (Serial.available() > 0) {
    int blinkCount = Serial.parseInt();
    for (int i = 0; i < blinkCount; i++) {
      digitalWrite(2, HIGH);
      delay(1000);
      digitalWrite(2, LOW);
      delay(1000);
    }

    int response = random(1, 10);
    Serial.println(response);
  }
}