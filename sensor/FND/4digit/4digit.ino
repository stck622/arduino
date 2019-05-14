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
  // put your setup code here, to run once:
  for (int i = 4; i <= 10; i++) {
    pinMode(i, OUTPUT);
  }
  for (int i = 0; i < 4; i++) {
    pinMode(14 + i, OUTPUT);
  }
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

  fnd_print(0);
  digitalWrite(17, LOW);
  delay(1);
  fnd_off();

  fnd_print(1);
  digitalWrite(16, LOW);
  delay(1);
  fnd_off();

  fnd_print(2);
  digitalWrite(15, LOW);
  delay(1);
  fnd_off();

  fnd_print(3);
  digitalWrite(14, LOW);
  delay(1);
  fnd_off();


}

//for (int j = 0; j < 10; j++) {
//  for (int i = 0; i <= 6; i++) {
//    digitalWrite(i + 3, fnd[j][i]);
//  }
//}

void loop() {
  // put your main code here, to run repeatedly:

  fnd_all_print(1, 2, 3, 4);

}
