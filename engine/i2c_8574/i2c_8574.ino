#define SCL 21
#define SDA 20

#define DEV_ID_PCF8574 0x27

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(SCL, OUTPUT);
  pinMode(SDA, OUTPUT);

  //standby
  digitalWrite(SCL, HIGH);
  digitalWrite(SDA, HIGH);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
void pcf_8574_data(char data) {

  for (int i = 0; i < 8; i ++) {
    digitalWrite(SDA, (data & (0X80 >> i)));
    digitalWrite(SCL, HIGH);
    digitalWrite(SCL, LOW);
  }

}

void pcf_8574_ack() {
  pinMode(SDA, INPUT);
  digitalWrite(SCL, HIGH);
  digitalWrite(SCL, LOW);
  pinMode(SDA, OUTPUT);
}

void pcf_8574_start() {
  //start
  digitalWrite(SDA, LOW);
  digitalWrite(SCL, LOW);
}

void pcf_8574_stop() {
  //stop
  digitalWrite(SDA, LOW);
  digitalWrite(SCL, HIGH);
  digitalWrite(SDA, HIGH);
}


void pcf_8574_set(char data) {

  pcf_8574_start();

  pcf_8574_data(DEV_ID_PCF8574 << 1);
  pcf_8574_ack();

  pcf_8574_data(data);
  pcf_8574_ack();

  pcf_8574_stop();

}
