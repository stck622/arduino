void setup() {
  // put your setup code here, to run once:
  DDRB = 0x20;
  TCCR2A = 0b00000000;
  TCCR2B = 0b00000100;
  TIMSK2 = 0b00000001;
  Serial.begin(9600);
  TCNT2 = 6;
}

void loop() {
  // put your main code here, to run repeatedly:

}

bool flag = false;
int count = 0;

SIGNAL(TIMER2_OVF_vect){
  count++;
  TCNT2 = 6;
  if(count > 1000){
    count = 0;
    if(flag)
    {
      PORTB = 0x20;
    }
    else
    {
      PORTB = 0x00;
    }
    flag = !flag;
  }
}
