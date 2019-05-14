int count = 0;
unsigned long ir_micro;
unsigned long ir_time_value[50];
unsigned long ir_offset_value[50];
bool toggle = false;
int k = 0;

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





void setup() {

  Serial.begin(9600);
  pinMode(4, INPUT);
  attachInterrupt(0, IR_INT, FALLING);
  for (int i = 4; i <= 10; i++) {
    pinMode(i, OUTPUT);
  }
  for (int i = 0; i < 4; i++) {
    pinMode(14 + i, OUTPUT);
  }
  fnd_all_print(0,0,0,0);
}

int fnd_print(int a) {
  for (int i = 0; i <= 6; i++) {
    digitalWrite(i + 4, fnd[a][i]);
  }
}

int fnd_off() {
  for (int i = 4; i <= 10; i++) {
    digitalWrite(i, LOW);
  }
  for (int i = 0; i < 4; i++) {
    digitalWrite(14 + i, HIGH);
  }
}

int fnd_all_print(int a, int b, int c, int d) {

  fnd_off();

  fnd_print(a);
  digitalWrite(17, LOW);
  delay(1);
  fnd_off();

  fnd_print(b);
  digitalWrite(16, LOW);
  delay(1);
  fnd_off();

  fnd_print(c);
  digitalWrite(15, LOW);
  delay(1);
  fnd_off();

  fnd_print(d);
  digitalWrite(14, LOW);
  delay(1);
  fnd_off();


}

void loop() {
  if (toggle) {
    toggle = false;
    //    for (int i = 18; i <= 25; i ++) {
    //      if (ir_offset_value[i] > 1000 && ir_offset_value[i] < 1500) {
    //        Serial.print("0");
    //      } else {
    //        Serial.print("1");
    //      }

    String str = "";

    for (int i = 18; i <= 25; i ++) {
      if (ir_offset_value[i] > 1000 && ir_offset_value[i] < 1500) {
        str += "0";
      } else {
        str += "1";
      }
    }

    for (int j = 0; j < 10; j++) {
        if (num[j] == str){
          Serial.println(String(j));
          k = j;
        }
    }
  }

  fnd_all_print(1,2,3,k);

}


void IR_INT() {

  ir_time_value[count] = micros();

  if (count > 0) {
    ir_offset_value[count] = ir_time_value[count] - ir_time_value[count - 1];
  }

  if (ir_offset_value[count] > 12000 && ir_offset_value[count] < 15000) {
    count = 1;
  }

  if (ir_offset_value[count] > 11000 && ir_offset_value[count] < 12000) {
    count = -1;
    toggle = true;
  }

  count++;
  if (count >= 34) {
    toggle = true;
    count = 0;
  }

}
