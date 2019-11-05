#define MOSI 11
#define CLK 13
#define LATCH 4
#define CS 10

void setup() {
  Serial.begin(9600);

  pinMode(11, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(10, OUTPUT);

  SPCR = 0x53; //SPI ENABLE

  spi_lcd(0x33, 0);
  spi_lcd(0x32, 0);
  spi_lcd(0x28, 0);
  spi_lcd(0x06, 0);
  spi_lcd(0x0C, 0);
  spi_lcd(0x80, 0);
  spi_lcd(0x01, 0);
  delay(5);

}
void loop() {
  spi_lcd(0x31, 1);
  delay(1000);
}

void spi_lcd(char data, char mode) {

  if (mode == 0)
    mode = 0x00;
  else
    mode = 0x01;

  spi_lcd_data((data & 0xf0), mode);
  spi_lcd_data(((data & 0x0f) << 4), mode);

}


//mode 0 : cmd, else data
void spi_lcd_data(char data, char mode) {

  spi(0x01);
  spi(data | mode);
  spi(data | 0x04 | mode);
  spi(data | mode);
  spi(0x01);

}

void spi(char data) {
  SPDR = data;
  while (!(SPSR & 0x80));
  latch();
  delayMicroseconds(100);
}

void latch() {
  digitalWrite(LATCH, HIGH);
  digitalWrite(LATCH, LOW);
}
