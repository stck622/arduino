/* 함수형 lcd 4비트  글자 출력 */

#define RS 2
#define E 4
#define DB4 9
#define DB5 10
#define DB6 11
#define DB7 12

bool toggle = true; //클릭시 false 해제시 true
int x = 0, y = 0;

int pinmap[4][20] =
{
  {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13},
  {0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3},
  {0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7},
  {0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF, 0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7}
};

void lcd_cmd(int num) {

  int tmp = 0x80;

  for (int i = 0; i < 2; i ++) {

    digitalWrite(RS, LOW);

    for (int j = 12; j >= 9; j--) {

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

  for (int i = 2; i <= 12; i++)
    pinMode(i, OUTPUT);

  digitalWrite(RS, HIGH);

  int command[] = {0x3, 0x3, 0x3, 0x2, 0x28, 0x0C, 0x06, 0x80, 0x01};

  for (int i = 0; i < sizeof(command) / sizeof(int) ; i++) {
    lcd_cmd(command[i]);
  }
  delay(1000);
}


void lcd_send(int num) {

  int tmp = 0x80;

  for (int i = 0; i < 2 ; i++) {

    digitalWrite(RS, HIGH);
    for (int j = 12; j >= 9; j--) {

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


char *a[4] = {"abcd",
           "efgh",
           "hijk",
           "lmno"
          };


void setup() {
  Serial.begin(9600);
  lcd_init();
  
  for(int j = 0; j < 4; j++){
    lcd_cmd(pinmap[j][0]);
    for(int i = 0; i < 4; i++){
      lcd_send(a[j][i]);
    }
  }
  
}


void loop() {

  
  
}
