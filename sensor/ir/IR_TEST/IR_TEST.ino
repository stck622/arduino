int i = 0;
unsigned long pre = 0;
int cnt = 0;
unsigned long ir_in_data[34];
unsigned long data[34];
unsigned long code[8];

const unsigned long data_code[10][8] =
{

  {0, 1, 1, 0, 1, 0, 0, 0},
  {0, 0, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 1, 1, 1, 1, 0, 1, 0},
  {0, 0, 0, 1, 0, 0, 0, 0},
  {0, 0, 1, 1, 1, 0, 0, 0},
  {0, 1, 0, 1, 1, 0, 1, 0},
  {0, 1, 0, 0, 0, 0, 1, 0},
  {0, 1, 0, 0, 1, 0, 1, 0},
  {0, 1, 0, 1, 0, 0, 1, 0},

};

int compare_value() {

  for (int k = 0; k < 10; k++) {
    bool flag2 = true;
    for (int y = 0; y < 8; y++) {
      if (code[y] != data_code[k][y]) {
        flag2 = false;
        break;
      }
    }
    if (flag2)
      return k;
  }
  return -1;
}


//18~25

void setup() {

  Serial.begin(9600);
  attachInterrupt(0, INT_0, FALLING);

}


void loop() {

  if (cnt == 1) {
    for (int j = 18 ; j < 26 ; j ++) {
      if ((data[j] < 1200) && (data[j] > 1000)) {
        // Serial.println(String(j) + " : 0");
        code[j - 18] = 0;

      } else  if ((data[j] < 2300) && (data[j] > 2200)) {
        //Serial.println(String(j) + " : 1");
        code[j - 18] = 1;
      }
    }

    Serial.println(compare_value());

    cnt = 0;
  } else if (cnt == 2) {
    //Serial.println("R");
    Serial.println(compare_value());
    cnt = 0;
  }

}


void INT_0() {

  ir_in_data[i] = micros();

  data[i] = ir_in_data[i] - ir_in_data[i - 1];

  if ((data[i] < 14000) && (data[i] > 12000)) {
    i = 1;
    cnt = 0;
  } else if ( (data[i] < 12000) && (data[i] > 10000) ) {
    i = -1;
    cnt = 2;
  }

  i++;

  if (i == 34) {
    i = 0;
    cnt = 1;
  }

}
