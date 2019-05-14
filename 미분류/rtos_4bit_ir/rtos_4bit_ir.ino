/* 함수형 lcd 4비트 이동기 */

#define RS 3
#define E 5
#define DB4 10
#define DB5 11
#define DB6 12
#define DB7 13

int k = 0;
bool toggle = false;
int count = 0;
unsigned long ir_time_value[50];
unsigned long ir_offset_value[50];

String num[10] {
  "01101000",
  "00110000",
  "00011000",
  "01111010",
  "00010000",
  "00111000",
  "01011010",
  "01000010",
  "01001010",
  "01010010",
};

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

  for (int i = 3; i <= 13; i++)
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
  attachInterrupt(0, IR_INT, FALLING);
  lcd_send('1');
}


void loop() {
    if (toggle) {
    toggle = false;
    //    for (int i = 18; i <= 25; i ++) {
    //      if (ir_offset_value[i] > 1000 && ir_offset_value[i] < 1500) {
    //        Serial.print("0");
    //      } else {
    //        Serial.print("1");
    //      }

    String str = "";

    for (int i = 18; i <= 25; i ++) {
      if (ir_offset_value[i] > 1000 && ir_offset_value[i] < 1500) {
        str += "0";
      } else {
        str += "1";
      }
    }

    for (int j = 0; j < 10; j++) {
        if (num[j] == str){
          Serial.println(String(j));
          lcd_send((j+'0'));
          k = j;
        }
    }
  }
}


void IR_INT() {
  ir_time_value[count] = micros();
 

  if (count > 0) {
    ir_offset_value[count] = ir_time_value[count] - ir_time_value[count - 1];
  }

  if (ir_offset_value[count] > 12000 && ir_offset_value[count] < 15000) {
    count = 1;
  }

  if (ir_offset_value[count] > 11000 && ir_offset_value[count] < 12000) {
    count = -1;
    toggle = true;
  }

  count++;
  if (count >= 34) {
    toggle = true;
    count = 0;
  }

}
