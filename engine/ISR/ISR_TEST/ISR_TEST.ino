
void setup() {

  Serial.begin(9600);
  attachInterrupt(0, INT_0, CHANGE);

}

unsigned long pre = 0;

void loop() {
}

void INT_0() {

  if (!digitalRead(2))
    pre = micros();
  else
    Serial.println(String(micros()-pre));
}
