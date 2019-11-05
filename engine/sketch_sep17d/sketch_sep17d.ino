void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  ADCSRA = 0x87;

  TCCR1A = 0x03;
  TCCR1B = 0x0A;
  TCCR1C = 0X00;
  TCNT1 = 1024 - 64;
  TIMSK1 = 0x01;

  TCCR3A = 0x03;
  TCCR3B = 0x0A;
  TCCR3C = 0X00;
  TCNT3 = 1024 - 64;
  TIMSK3 = 0x01;

}

int pos;
bool toggle[2];
int x_count = 0;
int y_count = 0;
int x_pos;
int y_pos;

int MyAnalogRead(int pin) {
  ADMUX = 0x40 | pin;
  ADCSRA |= 0x40;
  while (ADCSRA & 0x40);
  return ADC;
}

void loop() {
  // put your main code here, to run repeatedly:

  for (int i = 0; i < 2; i ++) {
    pos = MyAnalogRead(i);
    if (i) {
      x_pos = (((1025-lllpos)/1025.0)*50)+22;
    } else {l
      y_pos = ((pos/1025.0)*50)+22;
    }
  }
}

ISR(TIMER1_OVF_vect)
{
  x_count++;
  TCNT1 = 1024 - 64;

  if (x_count == 625) {
    x_count = 0;
    digitalWrite(8, HIGH);
  }

  if (x_count == x_pos) {
    digitalWrite(8, LOW);
  }

}

ISR(TIMER3_OVF_vect)        // interrupt service routine that wraps a user defined function supplied by attachInterrupt
{

  y_count++;
  TCNT3 = 1024 - 64;

  if (y_count == 625) {
    y_count = 0;
    digitalWrite(9, HIGH);
  }

  if (y_count == y_pos) {
    digitalWrite(9, LOW);
  }

}
