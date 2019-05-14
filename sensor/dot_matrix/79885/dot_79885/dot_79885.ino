#include <Servo.h>

#define DATA 2
#define SHC 3
#define LAT 4

Servo myservo;

int arr[10][8] = {
  {0x00, 0x38, 0x44, 0x4c, 0x54, 0x64, 0x44, 0x38},
  {0x00, 0x10, 0x30, 0x50, 0x10, 0x10, 0x10, 0x7c},
  {0x00, 0x38, 0x44, 0x04, 0x08, 0x10, 0x20, 0x7c},
  {0x00, 0x38, 0x44, 0x04, 0x18, 0x04, 0x44, 0x38},
  {0x00, 0x08, 0x18, 0x28, 0x48, 0x7c, 0x08, 0x08},
  {0x00, 0x7c, 0x40, 0x78, 0x04, 0x04, 0x44, 0x38},
  {0x00, 0x38, 0x40, 0x40, 0x78, 0x44, 0x44, 0x38},
  {0x00, 0x7c, 0x04, 0x08, 0x10, 0x20, 0x20, 0x20},
  {0x00, 0x38, 0x44, 0x44, 0x38, 0x44, 0x44, 0x38},
  {0x00, 0x38, 0x44, 0x44, 0x3c, 0x04, 0x44, 0x38}
};

void ic(int a, int b) {

  int tmp = 0x80;

  for (int i = 0; i < 8; i++) {
    digitalWrite(DATA, !(b & tmp));
    tmp >>= 1;
    digitalWrite(SHC, HIGH);
    digitalWrite(SHC, LOW);
  }

  tmp = 0x80;

  for (int i = 0; i < 8; i++) {
    digitalWrite(DATA, (a & tmp));
    tmp >>= 1;
    digitalWrite(SHC, HIGH);
    digitalWrite(SHC, LOW);
  }

  digitalWrite(LAT, HIGH);
  digitalWrite(LAT, LOW);
}

void off() {
  ic(0x00, 0x00);
}

void dot(int num, int li) {
  ic(0x80 >> li, arr[num][li]);
  off();
}

int count = 0;
int line = 0;

void keyread() {

  if (Serial.available()) {

    /*switch (Serial.read()) {
      case '1':
        count++;
        break;
      case '2':
        count--;
        break;
      }*/

    char value1 = Serial.read();
    if ('0' <= value1 && value1 <= '9') {
      count = ( value1 - '0');
      myservo.write(count*10);
      Serial.print(String(value1 - '0'));
    }


  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(DATA, OUTPUT);
  pinMode(SHC, OUTPUT);
  pinMode(LAT, OUTPUT);
  myservo.attach(9);
  Serial.begin(9600);
}

unsigned long pre1 = 0;
unsigned long pre2 = 0;
bool flag3 = true;
void loop() {
  keyread();
  unsigned long cur = micros();
  if (cur - pre1 >= 100) {


    pre1 = cur;

    dot(count, line);

    line++;

    if (line == 9) {
      line = 0;
    }

  }
  /*
    if (cur - pre2 >= 500000) {
    pre2 = cur;
    count++;
    if(count == 10){
      count = 0;
    }
    }*/

}
