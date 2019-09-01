String str1 = "";
unsigned long cur, pre;
int ser = 0;

int ser_dgree[7] =
{
  574, 574, 974, 974, 974, 974, 974
};

void setup() {
  // put your setup code here, to run once:
  DDRC = 0x3F;
  PORTC = 0x00;
  TCCR1A = 0x03;
  TCCR1B = 0x0B;
  TCNT1 = 399;
  OCR1A =  574;
  TIMSK1 = 0x03;
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readString();
    int tmp = atoi(input.c_str());
    Serial.println((input[0] - '0'));
    ser_dgree[(input[0] - '0')] = ((tmp - ((input[0] - '0') * 1000)));
    Serial.println(ser_dgree[(input[0] - '0')]);
  }
}

SIGNAL(TIMER1_OVF_vect) {

  TCNT1 = 399;

  ser++;
  if (ser == 8) {
    ser = 0;
  }
  
  PORTC |= (0x01 << ser);

  OCR1A = ser_dgree[(ser == 7 ? 0 : ser+1)]

}

SIGNAL(TIMER1_COMPA_vect) {
  PORTC &= ~(0x01 << ser);
}
