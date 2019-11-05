#define RS 2
#define RW 3
#define E 4

#define D0 5
#define D7 12

unsigned short lcd_map[64][8] = {{0, 0, 0,}, };

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
      lcd_graphic_data(1, x, y);
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
      lcd_graphic_data(1, x, y);
    }
  }

}


//0 => cmd, 1 => data
void lcd_8bit(unsigned char data, bool cmd) {

  digitalWrite(RS, HIGH);
  digitalWrite(RS, cmd);

  for (int i = 0; i < 8; i++) {
    digitalWrite( (12 - i), (data & (0x80 >> i)));
  }

  digitalWrite(E, HIGH);
  digitalWrite(E, LOW);

  digitalWrite(RS, HIGH);

  delayMicroseconds(200);
}

void lcd_graphic_data_coordinate(unsigned short data, int x, int y) {

  lcd_map[x][y] = (lcd_map[x][y] & (~data));
  lcd_map[x][y] = (lcd_map[x][y] | data);

  lcd_8bit(0X36, 0);
  lcd_8bit(0x80 + (y % 32), 0); //y
  lcd_8bit(0x80 + (y / 32) * 8 + x, 0); //x

  lcd_8bit(0X30, 0);
  lcd_8bit(((lcd_map[x][y] & 0xff00) >> 8), 1);
  lcd_8bit((lcd_map[x][y] & 0xff), 1);

  

}

void lcd_graphic_data(bool data, long x, long y) {

  lcd_graphic_data_coordinate(( (data ? 0x8000 : 0x0000) >> (x % 16)), (x / 16), y);

}

void lcd_clear() {
  for (int i = 0; i < 8; i ++) {
    for (int j = 0; j < 64; j ++) {
      lcd_graphic_data_coordinate(0, i, j);
    }
  }
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  for (int i = 2; i < 13; i++) {
    pinMode(i, OUTPUT);
  }

  lcd_8bit(0X30, 0);
  lcd_8bit(0X30, 0);
  lcd_8bit(0X30, 0);

  lcd_8bit(0X30, 0);
  lcd_8bit(0X06, 0);
  lcd_8bit(0X0C, 0);
  lcd_8bit(0X80, 0);
  lcd_8bit(0X01, 0);
  delay(500);
  lcd_clear();
  delay(100);

  for (int i = 0 ; i < 64; i ++) {
    for (int j = 0; j < 8; j++) {
      lcd_map[j][i] = 0;
    }
  }

  Bresenham(10, 10, 10, 60);
  Bresenham(60, 60, 60, 10);
  
  Bresenham(60, 10, 10, 10);
  Bresenham(60, 60, 10, 60);

}



void loop() {
  // put your main code here, to run repeatedly:
}
