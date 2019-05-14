#define LED1 12
#define LED2 13

unsigned long  pertime = 0;
int count = 0;
int led1 = 0;
bool led1_edge = true;
int led2 = 100;
bool led2_edge = false;

void led() {

  if (led1 == 100)
    led1_edge = false;
  else if (led1 == 0)
    led1_edge = true;

  if (led2 == 100)
    led2_edge = false;
  else if (led2 == 0)
    led2_edge = true;

  if (led1_edge) led1++;
  else led1--;

  if (led2_edge) led2++;
  else led2--;

}

void setup() {
  Serial.begin(9600);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() {

  unsigned long curtime = micros();

  if (curtime - pertime > 100) {

    pertime = curtime;
    count++;

    if (count == 100) {
      led();
      count = 0;
      if (led1 != 0)
        digitalWrite(LED1, HIGH);
      if (led2 != 0)
        digitalWrite(LED2, HIGH);

    } 
    if (count == led1)
      digitalWrite(LED1, LOW);
     if (count == led2)
      digitalWrite(LED2, LOW);

  }

}
