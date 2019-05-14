#define SIZE 2


int count = 0;

int led_port[SIZE];
int led_per[SIZE];
bool led_edge[SIZE];

void led() {

  if ( led_per[0] == 100)
    led_edge[0] = false;
  else if ( led_per[0] == 0)
    led_edge[0] = true;

  if (led_per[1] == 100)
    led_edge[1] = false;
  else if (led_per[1] == 0)
    led_edge[1] = true;

  if (led_edge[0]) led_per[0]++;
  else led_per[0]--;

  if (led_edge[1]) led_per[1]++;
  else led_per[1]--;

}

void INT_COUNT() {
  if (count == 10000) {
    count = 0;
    led();
  }
  delayMicroseconds(100);
  count += 100;
}

int per(int ms) {
  return ms * 100;
}

void LED_1(int s, int p) {

  if (count <= per(p)) {
    digitalWrite(s, HIGH);
  } else
    digitalWrite(s, LOW);

}

void setup() {

  led_port[0] = 12;
  led_port[1] = 13;

  led_per[0] = 0;
  led_per[1] = 100;

  for (int i = 0; i < 2; i++)
    pinMode(led_port[i], OUTPUT);
}

void loop() {

  for (int i = 0; i < 2; i++)
    LED_1(led_port[i], led_per[i]);

  INT_COUNT();
}
