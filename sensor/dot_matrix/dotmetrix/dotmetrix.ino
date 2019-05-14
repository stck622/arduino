

void DDR_C(int n) {
  int tmp = 0b10000000;
  for (int i = 10; i <= 17; i++) {
    digitalWrite(i, !(tmp & n));
    tmp = tmp >> 1;
  }
}

void DDR_R(int n) {
  for (int i = 2; i <= 9; i++) {
    digitalWrite(i, (i - 2) == n);
  }
}

void OFF() {
  for (int i = 2; i <= 9; i++) {
    digitalWrite(i, LOW);
  }

  for (int i = 10; i <= 17; i++) {
    digitalWrite(i, HIGH);
  }
}

void dot(int arr[]) {

  for (int j = 0; j < 8; j++) {
    OFF();
    DDR_R(j);
    DDR_C(arr[j]);
  }

}

void setup() {
  // put your setup code here, to run once:

  for (int i = 0; i < 16; i++) {
    pinMode(i + 2, OUTPUT);
  }

  OFF();

}

/*
  핀맵

  2~9 COL //가로
  10~17 ROW //세로

*/

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

int count = 0;
unsigned long pre1 = 0;
unsigned long pre2 = 0;
int tmp[8];
int k = 0, l = 0;
void loop() {
  // put your main code here, to run repeatedly:
  unsigned long cur = micros();
 

  if (cur - pre2 >= 1000000) {
    pre2 = cur;
    //dot(arr[count]);
     memcpy(tmp,arr[l],sizeof(int)*8);
    for (int i = 0; i < 8; i++) {
      tmp[i] = tmp[i] >> k;
    }
    k++;
    if(k == 8){
      k = 0; 
      l++;
      if(l == 10){
        l = 0;
      }
    }
  }

  
  dot(tmp);
  /*
    if (cur - pre1 >= 1000000){
    pre1 = cur;
    count++;
    if(count == 10)
      count = 0;
    }*/



}
