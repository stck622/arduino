int count = 0;
unsigned long ir_micro;
unsigned long ir_time_value[50];
unsigned long ir_offset_value[50];
bool toggle = false;
int k = 0;


// IR 숫자 배열
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


//FND 숫자 배열
int fnd[10][7] {
  {1, 1, 1, 1, 1, 0, 1},
  {0, 0, 0, 0, 1, 0, 1},
  {1, 0, 1, 1, 0, 1, 1},
  {1, 0, 0, 1, 1, 1, 1},
  {0, 1, 0, 0, 1, 1, 1},
  {1, 1, 0, 1, 1, 1, 0},
  {0, 1, 1, 1, 1, 1, 0},
  {1, 1, 0, 0, 1, 0, 1},
  {1, 1, 1, 1, 1, 1, 1},
  {1, 1, 0, 0, 1, 1, 1,},
};


//fnd 출력
int fnd_print(int a) {
  for (int i = 0; i <= 6; i++) {
    digitalWrite(i + 4, fnd[a][i]);
  }
}

//fnd 전체 끄기
int fnd_off() {
  for (int i = 4; i <= 10; i++) {
    digitalWrite(i, LOW);
  }
  for (int i = 0; i < 4; i++) {
    digitalWrite(14 + i, HIGH);
  }
}

//fnd 전체 켜기
int fnd_all_print(int a, int b, int c, int d) {

  fnd_off();
  //fnd 전체 끄기

  fnd_print(a);
  digitalWrite(17, LOW);
  delay(1);
  fnd_off();
  //첫째자리 출력

  fnd_print(b);
  digitalWrite(16, LOW);
  delay(1);
  fnd_off();
  //둘째자리 출력

  fnd_print(c);
  digitalWrite(15, LOW);
  delay(1);
  fnd_off();
  //셋째자리 출력

  fnd_print(d);
  digitalWrite(14, LOW);
  delay(1);
  fnd_off();
  //넷째자리 출력

}

void setup() {

  attachInterrupt(1, IR_INT, FALLING);
  //IR 인터럽트

  for (int i = 4; i <= 10; i++) {
    pinMode(i, OUTPUT);
  }

  for (int i = 0; i < 4; i++) {
    pinMode(14 + i, OUTPUT);
  }
  //FND 인터럽트

  fnd_all_print(0, 0, 0, 0);
  //FND 0 초기화

}

void loop() {

  if (toggle) { //IR 데이터 갱신이 필요하다면
    toggle = false;

    String str = "";
    //STR

    for (int i = 18; i <= 25; i ++) {
      //18부터 25까지 data 테스트.
      
      if (ir_offset_value[i] > 1000 && ir_offset_value[i] < 1500) { //
        //IR 값 분석
        
        str += "0";
        //0값
        
      } else {
        
        str += "1";
        //1값
        
      }
      
    }

    for (int j = 0; j < 10; j++) {
      if (num[j] == str) {
        k = j;
      }
    }
  }
  //IR 수신값 대조

  fnd_all_print(1, 2, 3, k);
  //FND전체 출력

}


void IR_INT() {
  //IR 인터럽트

  ir_time_value[count] = micros();
  //현재 시간

  if (count > 0) {
    ir_offset_value[count] = ir_time_value[count] - ir_time_value[count - 1];
  }
  //데이터 간격 저장

  if (ir_offset_value[count] > 12000 && ir_offset_value[count] < 15000) {
    count = 1;
  }
  //리드 값 확인

  if (ir_offset_value[count] > 11000 && ir_offset_value[count] < 12000) {
    count = -1;
    toggle = true;
  }
  //리피트 값 확인

  count++;
  if (count >= 34) {
    toggle = true;
    count = 0;
  }
  //값 다오면 초기화

}
