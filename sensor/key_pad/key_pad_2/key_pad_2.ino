bool flag[4][4];
int input[4] = {2, 3, 4, 5};
int output[4] = {6, 7, 8, 9};

int fnd_pin[8] = {12, 13, 14, 15, 16, 17, 18, 19};
int fnd_char[10][8] = {
  {0, 0, 1, 1, 1, 1, 1, 1},
  {0, 0, 0, 0, 0, 0, 1, 1},
  {1, 0, 1, 0, 1, 1, 0, 1},
  {1, 0, 1, 0, 1, 0, 1, 1},
  {1, 0, 0, 1, 0, 0, 1, 1},
  {1, 0, 1, 1, 1, 0, 1, 0},
  {1, 0, 1, 1, 1, 1, 1, 0},
  {0, 0, 1, 1, 0, 0, 1, 1},
  {1, 0, 1, 1, 1, 1, 1, 1},
  {1, 0, 1, 1, 0, 0, 1, 1},
};

int key[4][4] = {{1, 2, 3, 0}, {4, 5, 6, 0}, {7, 8, 9, 0}, {0, 0, 0, 0}};


unsigned long pre1 = 0;
unsigned long pre2 = 0;

int j = 0;
bool k = 0;
int n = 0;

void bt_read() {

  for (int i = 0; i < 4; i++) {

    if (digitalRead(input[i]) && flag[j][i] == false) {
      flag[j][i] = true;
      n = key[i][j];
    } else if ((!digitalRead(input[i])) && flag[j][i] == true) {
      flag[j][i] = false;
      n = key[i][j];
    }

  }

}

void fnd(int n) {

  digitalWrite(10, LOW);
  digitalWrite(11, LOW);

  for (int i = 0; i < 8; i++) {
    digitalWrite(fnd_pin[i], HIGH);
  }

  for (int i = 0; i < 8; i++) {
    digitalWrite(fnd_pin[i], !fnd_char[n][i]);
  }
}

void setup() {
  // put your setup code here, to run once:
  for (int j = 0; j < 4; j++) {
    pinMode(output[j], OUTPUT);
    digitalWrite(output[j], LOW);
  }

  for (int j = 0; j < 4; j++) {
    pinMode(input[j], INPUT);
  }

  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  for (int i = 0; i <  8; i++) {
    pinMode(fnd_pin[i], OUTPUT);
  }

  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);

  Serial.begin(9600);

}

void loop() {

  unsigned long cur = millis();

  if (cur - pre1 >= 10) {

    pre1  = cur;

    digitalWrite(output[j], HIGH); // 열 아웃풋
    bt_read();
    digitalWrite(output[j], LOW); // 열 아웃풋

    j++;

    if (j == 4) {
      j = 0;
    }

  }



  if (cur - pre2 >= 10) {
    pre2 = cur;
    if (k) {
      fnd(n);
      digitalWrite(11, HIGH);
    } else {
      fnd(2);
      digitalWrite(10, HIGH);
    }

    k = !k;
  }
}
