
#define RS 3
#define E 5
#define DB4 10
#define DB5 11
#define DB6 12
#define DB7 13

void lcd_cmd(int num) {

  int tmp = 0x80;
 
  for (int i = 0; i < 2; i ++) {

    digitalWrite(RS, LOW);

    for (int j = 13; j >= 10; j--) {

      

      if (num & tmp)
        digitalWrite(j, HIGH);
      else
        digitalWrite(j, LOW);

      tmp >>= 1;

    }

    digitalWrite(E, HIGH);
    digitalWrite(E, LOW);

    digitalWrite(RS, HIGH);

    delayMicroseconds(100);
  }

}


void lcd_init() {

  for (int i = 2; i <= 13; i++)
    pinMode(i, OUTPUT);

  digitalWrite(RS, HIGH);

  int command[] = {0x3, 0x3, 0x3, 0x2, 0x28, 0x0C, 0x06,0x80,0x01};

  for (int i = 0; i < sizeof(command) / sizeof(int) ; i++) {
    lcd_cmd(command[i]);
  }
  delay(1000);
}


void lcd_send(int num) {

  int tmp = 0x80;

  for (int i = 0; i < 2 ; i++) {

    digitalWrite(RS, HIGH);
    for (int j = 13; j >= 10; j--) {

      if (num & tmp)
        digitalWrite(j, HIGH);
      else
        digitalWrite(j, LOW);

      tmp >>= 1;

    }

    digitalWrite(E, HIGH);
    digitalWrite(E, LOW);
    digitalWrite(RS, HIGH);

    delayMicroseconds(100);
  }
}


void setup() {
  Serial.begin(9600);
  lcd_init();
}


void loop() {
  lcd_send('1');
  delay(1000);
}
