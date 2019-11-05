int arr[] = {0, 0, 1, 1, 0, 0, 0, 1};

void setup() {
  pinMode(1, OUTPUT);
  digitalWrite(1, HIGH);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(1, LOW);
  delayMicroseconds(102);
  digitalWrite(1, HIGH);
  delayMicroseconds(102);
  digitalWrite(1, LOW);
  delayMicroseconds(102);
  digitalWrite(1, LOW);
  delayMicroseconds(102);
  digitalWrite(1, LOW);
  delayMicroseconds(102);
  digitalWrite(1, HIGH);
  delayMicroseconds(102);
  digitalWrite(1, HIGH);
  delayMicroseconds(102);
  digitalWrite(1, LOW);
  delayMicroseconds(102);
  digitalWrite(1, LOW);
  delayMicroseconds(102);
  digitalWrite(1, HIGH);
  delayMicroseconds(102);
  digitalWrite(1, HIGH);
  delayMicroseconds(102);
  delay(1000);
}
