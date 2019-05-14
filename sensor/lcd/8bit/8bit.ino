#define RS 3
#define RW 4
#define EN 5

#define D0 6
#define D1 7
#define D2 8
#define D3 9
#define D4 10
#define D5 11
#define D6 12
#define D7 13

void lcd_send_cmd(unsigned char  x) {

  digitalWrite(RS, LOW);
  digitalWrite(RW, LOW);

  unsigned char tmp = 0x01;

  for (int i = 0; i < 8; i++) {
    
    digitalWrite(i+6, (tmp & x) > 0 ? HIGH : LOW);
    tmp  = tmp << 1;;
  }

  digitalWrite(EN, HIGH);
  digitalWrite(EN, LOW);

  digitalWrite(RW, HIGH);
  digitalWrite(RS, HIGH);

  delayMicroseconds(100);
}

void lcd_send_data(unsigned char  x) {

  digitalWrite(RS, HIGH);
  digitalWrite(RW, LOW);

  unsigned char tmp = 0x01;

  for (int i = 0; i < 8; i++) {
    
    digitalWrite(i+6, (tmp & x) > 0 ? HIGH : LOW);
    tmp  = tmp << 1;;
  }

  digitalWrite(EN, HIGH);
  digitalWrite(EN, LOW);

  digitalWrite(RW, HIGH);
  digitalWrite(RS, HIGH);

  delayMicroseconds(100);
}

void setup() {
  // put your setup code here, to run once:

  for (int i = 3; i <= 13; i ++) {
    pinMode(i, OUTPUT);
  }

  Serial.begin(9600);

  digitalWrite(RW, HIGH);
  digitalWrite(RS, HIGH);

  delay(2);

  lcd_send_cmd(0x30);
  lcd_send_cmd(0x30);
  lcd_send_cmd(0x30);

  lcd_send_cmd(0x38);
  lcd_send_cmd(0x06);
  lcd_send_cmd(0x0C);
  lcd_send_cmd(0x80);

  lcd_send_cmd(0x01);

  delay(2);
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd_send_data(0x31);
  delay(1000);

  
}
