/*음계*/
#define C_3 8
#define D_3 9
#define E_3 10
#define F_3 11
#define G_3 12
#define A_3 13
#define B_3 14

int row[] = {2, 3, 4, 5};//ROW 핀
int col[] = {6, 7, 8, 9};//COL 핀

/*키패드 위치 계이름*/
int melody[3][3] = {
  {8, 9, 10},
  {11, 12, 13},
  {14, 0, 0}
};

/*HZ TO MICRO*/
double hz_to_us(double hz) {
  return round(((1 / hz) * 1000000) / 2);
}

//계이름 hz
double sy[] = {

  0,

  //3옥타브
  130.8128, //도
  146.8324, //레
  164.6141, //미
  174.6141, //파
  195.9977, //솔
  220.0000, //라
  246.9417, //시

  //4옥타브
  261.6256, //도
  293.6648, //레
  329.6276, //미
  349.2282, //파
  391.9954, //솔
  440.0000, //라
  493.8833, //시

  //5옥타브
  523.2511, //도
  587.3295, //레
  659.2551, //미
  698.4565, //파
  783.9909, //솔
  880.0000, //라
  987.7666, //시

};


int count = 1;  //계이름 인덱스
bool flag2; //high low 부저

unsigned long long pre_ml = 0;
unsigned long long pre_mic = 0;
unsigned long long pre_mic_2 = 0;

unsigned long long cur_ml;
unsigned long long cur_mic;

void setup() {
  // put your setup code here, to run once:

  pinMode(10, OUTPUT); //부저

  /*hz to micro*/
  for (int i = 0; i < (sizeof(sy) / sizeof(double)); i++ ) {
    sy[i] = hz_to_us(sy[i]);
  }


  /*COL*/
  for (int i = 0; i < 4; i++) {
    pinMode(col[i], INPUT);
    digitalWrite(col[i], HIGH); //풀업저항 활성화
  }

  /*ROW*/
  for (int i = 0; i < 4; i++) {
    pinMode(row[i], OUTPUT);
    digitalWrite(row[i], HIGH);
  }

}

void loop() {

  cur_mic = micros();
  cur_ml = millis();

  if (cur_mic - pre_mic >= sy[count]) { //주파수 값
    pre_mic = cur_mic;
    digitalWrite(10, count ? (flag2 = !flag2) : 0);//flag 에 의한 high low, count 0 이면 출력x
  }

  for (int i = 0; i < 3; i++) {
    digitalWrite(row[i], LOW);
    for (int j = 0; j < 3; j++) {
      if (!digitalRead(col[j])) {
        count = melody[i][j]; //카운트 키패드 계이름 할당
      }
    }
    digitalWrite(row[i], HIGH);
  }
  
}
