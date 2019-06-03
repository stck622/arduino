#define NONE 0
#define C_3 1
#define D_3 2
#define E_3 3
#define F_3 4
#define G_3 5
#define A_3 6
#define B_3 7

#define C_3 8
#define D_3 9
#define E_3 10
#define F_3 11
#define G_3 12
#define A_3 13
#define B_3 14

#define C_3 15
#define D_3 16
#define E_3 17
#define F_3 18
#define G_3 19
#define A_3 20
#define B_3 21

#define melody_4 250
#define melody_2 500
#define melody_1 1000

double hz_to_us(double hz) {
  return round(((1 / hz) * 1000000) / 2);
}

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

int school_paper_dang_dang_dang[][2] = {
  {G_3, melody_4},
  {G_3, melody_4},
  {A_3, melody_4},
  {A_3, melody_4},
  {G_3, melody_4},
  {G_3, melody_4},
  {E_3, melody_2},
  {G_3, melody_4},
  {G_3, melody_4},
  {E_3, melody_4},
  {E_3, melody_4},
  {D_3, melody_1},
  {G_3, melody_4},
  {G_3, melody_4},
  {A_3, melody_4},
  {A_3, melody_4},
  {G_3, melody_4},
  {G_3, melody_4},
  {E_3, melody_2},
  {G_3, melody_4},
  {E_3, melody_4},
  {D_3, melody_4},
  {E_3, melody_4},
  {C_3, melody_1},
};

bool flag;
bool off;
unsigned long long pre_ml = 0;
unsigned long long pre_ml_2 = 0;
unsigned long long pre_mic = 0;

unsigned long long cur_ml;
unsigned long long cur_mic;

void setup() {
  // put your setup code here, to run once:
  pinMode(10, OUTPUT);
  for (int i = 0; i < (sizeof(sy) / sizeof(double)); i++ ) {
    sy[i] = hz_to_us(sy[i]);
  }
}
int count = 0;
void loop() {

  cur_mic = micros();
  cur_ml = millis();

  if (cur_mic - pre_mic >= sy[school_paper_dang_dang_dang[count][0]]) {
    pre_mic = cur_mic;
    digitalWrite(10, off ? 0:(flag = !flag));
  }

  if(cur_ml - pre_ml_2 >= 75){
    off = false;
  }

  if (cur_ml - pre_ml > school_paper_dang_dang_dang[count][1]+75) {
    pre_ml = cur_ml;
    pre_ml_2 = millis();
    off = true;
    count++;
    if (count == (sizeof(school_paper_dang_dang_dang) / sizeof(school_paper_dang_dang_dang[0])) ) {
      count = 0;
    }
  }

}
