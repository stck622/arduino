void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);

}

void loop() {
  for (int i = 0; i < 10000; i += 100) {
    for (int j = 0; j < 10; j++) {
      digitalWrite(13, HIGH);
      delayMicroseconds(10000 - i);
      digitalWrite(13, LOW);
      delayMicroseconds(i);
    }
  }
}
