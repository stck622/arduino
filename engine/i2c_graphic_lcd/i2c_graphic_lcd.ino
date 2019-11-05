#define SCL 21
#define SDA 20

#define DEV_ID_PCF8574 0x27

unsigned short lcd_map[16][32];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  for (int i = 0 ; i < 16; i ++) {
    for (int j = 0; j < 32; j ++) {
      lcd_map[i][j] = 0;
    }
  }

  pinMode(SCL, OUTPUT);
  pinMode(SDA, OUTPUT);

  //standby
  digitalWrite(SCL, HIGH);
  digitalWrite(SDA, HIGH);

  graphic_lcd_data(0x33, 0);
  graphic_lcd_data(0x32, 0);
  graphic_lcd_data(0x28, 0);
  graphic_lcd_data(0x06, 0);
  graphic_lcd_data(0x0C, 0);
  graphic_lcd_data(0x80, 0);
  graphic_lcd_data(0x01, 0);
  delay(1000);
  graphic_lcd_clear();
  delay(1000);
  graphic_lcd_draw(1, 0, 0);

  Bresenham(10, 10, 10, 60);
  Bresenham(60, 60, 60, 10);

  Bresenham(60, 10, 10, 10);
  Bresenham(60, 60, 10, 60);
}

void loop() {
  // put your main code here, to run repeatedly:

  delay(1000);

}

void pcf_8574_data(char data) {

  for (int i = 0; i < 8; i ++) {
    digitalWrite(SDA, (data & (0X80 >> i)));
    digitalWrite(SCL, HIGH);
    digitalWrite(SCL, LOW);
  }

}

void pcf_8574_ack() {
  pinMode(SDA, INPUT);
  digitalWrite(SCL, HIGH);
  digitalWrite(SCL, LOW);
  pinMode(SDA, OUTPUT);
}

void pcf_8574_start() {
  //start
  digitalWrite(SDA, LOW);
  digitalWrite(SCL, LOW);
}

void pcf_8574_stop() {
  //stop
  digitalWrite(SDA, LOW);
  digitalWrite(SCL, HIGH);
  digitalWrite(SDA, HIGH);
}


void pcf_8574_set(char data) {

  pcf_8574_start();

  pcf_8574_data(DEV_ID_PCF8574 << 1);
  pcf_8574_ack();

  pcf_8574_data(data);
  pcf_8574_ack();

  pcf_8574_stop();

  delayMicroseconds(100);

}

//0 : cmd, 1 : data
void graphic_lcd_data_4bit(char data, char cmd) {

  pcf_8574_set(0x01);
  pcf_8574_set(cmd);

  pcf_8574_set(data | cmd);
  pcf_8574_set(data | cmd | 0x04);
  pcf_8574_set(data | cmd);

  pcf_8574_set(cmd);
  pcf_8574_set(0x01);

  delayMicroseconds(100);
}

void graphic_lcd_data(char data, char cmd) {

  if (cmd == 0) {
    cmd = 0x00;
  } else {
    cmd = 0x01;
  }

  graphic_lcd_data_4bit((data & 0xf0) , cmd);
  graphic_lcd_data_4bit((data & 0xf) << 4, cmd);

}

void graphic_lcd_data_cordinate(unsigned short data, int x, int y) {

  graphic_lcd_data(0X26, 0);
  graphic_lcd_data(0x80 + (y % 32), 0); //y
  graphic_lcd_data(0x80 + (y / 32) * 8 + x, 0); //x

  lcd_map[(y % 32)][((y / 32) * 8 + x)] |= data;
  
  graphic_lcd_data(0X20, 0);
  graphic_lcd_data((( lcd_map[(y % 32)][((y / 32) * 8 + x)] & 0xff00) >> 8), 1);
  graphic_lcd_data(( lcd_map[(y % 32)][((y / 32) * 8 + x)] & 0xff), 1);

}

void graphic_lcd_data_clear_cordinate(unsigned short data, int x, int y) {

  graphic_lcd_data(0X26, 0);
  graphic_lcd_data(0x80 + (y % 32), 0); //y
  graphic_lcd_data(0x80 + (y / 32) * 8 + x, 0); //x
  
  graphic_lcd_data(0X20, 0);
  graphic_lcd_data(((data & 0xff00) >> 8), 1);
  graphic_lcd_data((data & 0xff), 1);

}

void graphic_lcd_clear() {
  for (int i = 0; i < 8; i ++) {
    for (int j = 0; j < 64; j ++) {
      graphic_lcd_data_clear_cordinate(0, i, j);
    }
  }
}

void graphic_lcd_draw(bool data, long x, long y) {

  graphic_lcd_data_cordinate(( (data ? 0x8000 : 0x0000) >> (x % 16)), (x / 16), y);

}

void Bresenham(int x1, int y1, int x2, int y2)
{
  int addX, addY;
  int counter = 0;

  int dx = x2 - x1;
  int dy = y2 - y1;

  //음수 방향으로 진행될 경우
  if (dx < 0)
  {
    addX = -1;
    dx = -dx;
  }
  else
  {
    addX = 1;
  }

  //음수 방향으로 진행될 경우
  if (dy < 0)
  {
    addY = -1;
    dy = -dy;
  }
  else
  {
    addY = 1;
  }

  int x = x1;
  int y = y1;

  //dx >= dy 일 경우( 기울기 < 1) y의 조건이 만족하면 y를 1증가시킨다
  if (dx >= dy)
  {
    for (int i = 0; i < dx; i++)
    {
      //x를  1증가 시키고 dy만큼 Count 증가
      x += addX;
      //x의 증가값만큼 Count 증가
      counter += dy;

      //증가하는 y값 보다 크다면
      if (counter >= dx)
      {
        // y를 1증가 시키고 Count를 초기화한다
        y += addY;
        counter -= dx;
      }
      graphic_lcd_draw(1, x, y);
    }
  }
  //dx < dy 일 경우( 기울기 > 1) x의 조건이 만족하면 y를 1증가시킨다
  else
  {
    for (int i = 0; i < dy; i++)
    {
      //y를  1증가 시키고 dx만큼 Count 증가
      y += addY;
      counter += dx;

      //증가하는 y값 보다 크다면
      if (counter >= dy)
      {
        // x를 1증가 시키고 Count를 초기화한다
        x += addX;
        counter -= dy;
      }
      graphic_lcd_draw(1, x, y);
    }
  }

}
