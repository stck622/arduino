// I2C input : SDA(AD4), SCL(AD5)
// I2C output : 8 bit ( 4,5,6,7, 8,9,10,11 )

#include <Wire.h>

#define SLAVE_ID  0x27

int i,j;

void receiveEvent(int howMany) {
  if(Wire.available()) { 
    char read_value = Wire.read(); 
    //Serial.print(read_value);  

    for(i=0;i<8;i++){
      if(read_value & (0x80 >> i)){
        digitalWrite(4 + (7-i), HIGH);
      }

      else{

        digitalWrite(4 + (7-i), LOW);
      }
    }
  }
}

void setup() {
  Serial.begin(9600); 
    
  Wire.begin(SLAVE_ID);               
  Wire.onReceive(receiveEvent); 

  for(i=0;i<8;i++)
    pinMode(4+i,OUTPUT);

  delay(2000);

  setup_custom();
}

//===============================
//===============================
// custom code

#define SDA 2
#define SCL 3

void setup_custom()
{
  
}

void loop() {
  delay(1);
}


//==============================
