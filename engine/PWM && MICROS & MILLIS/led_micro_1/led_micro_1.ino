#define LED1 12
#define LED2 13

unsigned long  pertime = 0;
int count = 0;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() {

  unsigned long curtime = micros();

  if (curtime - pertime > 100) {

    pertime = curtime;
    count++;

    if (count == 100) {

      count = 0;
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);

    } else if (count == 10)
      digitalWrite(LED1, LOW);
    else if (count == 50)
      digitalWrite(LED2, LOW);

  }

}
