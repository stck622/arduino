void setup() {
  // put your setup code here, to run once:
  pinMode(33, INPUT);
  digitalWrite(33, HIGH);
  pinMode(31, INPUT);
  digitalWrite(31, HIGH);
  Serial.begin(9600);
}

double flag_31 = false;
double flag_33 = false;

int state = 0;

//31, 33
void loop() {
  // put your main code here, to run repeatedly:

  int EN1;
  int EN2;

  EN1 = digitalRead(31);
  EN2 = digitalRead(33);

  //Serial.println("EN1" + String(read_val1));
  //Serial.println("EN2" + String(read_val2));
  //Serial.println("\n");

  /*if (read_val1 == LOW && flag_31 == false) {
    flag_31 = true;
    Serial.println("EN1 : " + String(read_val1));
    }
    if (read_val1 == HIGH && flag_31 == true) {
    flag_31 = false;
    Serial.println("EN1 : " + String(read_val1));
    }

    if (read_val2 == LOW && flag_33 == false) {
    flag_33 = true;
    Serial.println("EN2 : " + String(read_val2));
    }
    if (read_val2 == HIGH && flag_33 == true) {
    flag_33 = false;
    Serial.println("EN2 : " + String(read_val2));
    }*/


  /* state 0 */
  if (state == 0) {

    if (EN1 == LOW)
      state = 1;

    if (EN2 == LOW)
      state = 11;
  }


  /* Right */

  if (state == 1) {

    if (EN2 == LOW)
      state = 2;
    if (EN1 == HIGH)
      state = 0;
  }

  if (state == 2) {

    if (EN1 == HIGH && EN2 == LOW)
      state = 3;
  }

  if (state == 3) {
    if (EN1 == HIGH && EN2 == HIGH) {
      state = 0;
      Serial.println("RIGHT");
    }
  }

//24 e0 en, 26 e0 step, 28 e0 dir
  /* Left */
  if (state == 11) {

    if (EN2 == HIGH)
      state = 0;
    if (EN1 == LOW)
      state = 12;
  }

  if (state == 12) {

    if (EN1 == LOW && EN2 == HIGH)
      state = 13;
  }

  if (state == 13) {
    if (EN1 == HIGH && EN2 == HIGH) {
      state = 0;
      Serial.println("LEFT");
    }
  }
  
  delay(1);
  
}
