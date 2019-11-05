void setup() {
  // put your setup code here, to run once:

  DDRD &= ~0x01; //uart rx
  DDRD |= 0x02; //uart tx

  UCSR0A = 0x00; //flag
  UCSR0B = 0x98; //tx rx enable
  UCSR0C = 0x06; //async, parity, 8 n 1
  UBRR0 = 103; //baudrate

}

ISR(USART_RX_vect)
{
    char aa = UDR0;
    while(!(UCSR0A & 0x20));
    UDR0 = aa;
    
}

unsigned char data[10] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39};
int i;
void loop() {
  // put your main code here, to run repeatedly:
 
  /*(for (i = 0; i < 10; i ++){
    while(!(UCSR0A & 0x20));
    UDR0 = data[i];
  }*/

}

/*
 * UBRR0 : baudrate
 * UDR0 : data
 * USCR0A : flag, empty
 * USCR0B : int enable
 * USCR0C : Async, parity, stop, bit
 */
