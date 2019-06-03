void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("connect");
  DDRD &= (~0x40);
}

bool flag = true;

void loop() {
  // put your main code here, to run repeatedly:
  if (flag != ((PIND & 0x04) != 0? true : false)) {
    flag = PIND & 0x04;
    Serial.println("ch");
  }
}
