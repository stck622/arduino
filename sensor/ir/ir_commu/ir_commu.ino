

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(4, INPUT);
  attachInterrupt(1, IR_INT, FALLING);

}

int count = 0;
unsigned long ir_micro;
unsigned long ir_time_value[50];
unsigned long ir_offset_value[50];

void loop() {
  // put your main code here, to run repeatedly:
}

void IR_INT() {

  ir_micro = micros();
  ir_time_value[count] = micros();

  if (count > 0) {
    ir_offset_value[count] = ir_time_value[count] - ir_time_value[count - 1];
  }

  if (ir_offset_value[count] > 12000 && ir_offset_value[count] < 15000) {
    count = 1;
  }

  if (ir_offset_value[count] > 11000 && ir_offset_value[count] < 12000) {
    count = -1;
    Serial.println("r");
  }

  count++;
  if (count >= 34) {
    count = 0;
    for (int i = 0; i <= 25; i ++) {
//      if (ir_offset_value[i] > 1000 && ir_offset_value[i] < 1500) {
//        Serial.print("0");
//      } else {
//        Serial.print("1");
//      }
        Serial.println(String(i) + " : " + ir_offset_value[i]);
    }
    Serial.print("\n");
  }

}
