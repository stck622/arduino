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
  count++;
  if(count >= 34){
    count = 0;
    for(int i = 0; i <= 50; i ++){
      Serial.println(ir_time_value[i]);
    }
  }

}
