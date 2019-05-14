bool flag[4][4];
int input[4] = {2, 3, 4, 5};
int output[4] = {6, 7, 8, 9};

void setup() {
  // put your setup code here, to run once:
  for (int j = 0; j < 4; j++) {
    pinMode(output[j], OUTPUT);
    digitalWrite(output[j], LOW);
  }

  for (int j = 0; j < 4; j++) {
    pinMode(input[j], INPUT);
  }

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  for (int j = 0; j < 4; j++) {

    digitalWrite(output[j], HIGH); // 열 아웃풋

    for (int i = 0; i < 4; i++) { //행 인풋

      if (digitalRead(input[i]) && flag[j][i] == false) {
        flag[j][i] = true;
        Serial.println("UP " + String(i) + String(j));
      } else if ((!digitalRead(input[i])) && flag[j][i] == true) {
        flag[j][i] = false;
        Serial.println("DOWN " + String(i) + String(j));
      }

      delay(10);

    }

    digitalWrite(output[j], LOW);

  }

}
