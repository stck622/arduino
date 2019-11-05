#define RS 2
#define RW 3
#define E 4

#define CS RS
#define SCLK E
#define SID RW

#define D0 5
#define D7 12

void graphicLCD_serial_data(char data) {
  digitalWrite(CS, HIGH);
  shiftOut(SID, SCLK, MSBFIRST, 0xFA);
  shiftOut(SID, SCLK, MSBFIRST, data & 0xF0);
  shiftOut(SID, SCLK, MSBFIRST, (data & 0x0F) << 4);
  digitalWrite(CS, LOW);
}

void graphicLCD_serial_cmd(char data) {
  digitalWrite(CS, HIGH);
  shiftOut(SID, SCLK, MSBFIRST, 0xF8);
  shiftOut(SID, SCLK, MSBFIRST, data & 0xF0);
  shiftOut(SID, SCLK, MSBFIRST, (data & 0x0F) << 4);
  digitalWrite(CS, LOW);
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  for (int i = 2; i < 13; i++) {
    pinMode(i, OUTPUT);
  }

  graphicLCD_serial_cmd(0x30);
  graphicLCD_serial_cmd(0x30);
  graphicLCD_serial_cmd(0x30);

  graphicLCD_serial_cmd(0x38);
  graphicLCD_serial_cmd(0x06);
  graphicLCD_serial_cmd(0x0C);
  graphicLCD_serial_cmd(0x80);
  graphicLCD_serial_cmd(0x01);
  delay(100);

}



void loop() {
  graphicLCD_serial_data(0x31);
}
