#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CSN, CE
const byte address[6] = "00001";

int x_key = A1;                                               
int y_key = A0;                                               
int x_pos;
int y_pos;

int dir[2];

void setup() {

  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  pinMode (x_key, INPUT) ;                     
  pinMode (y_key, INPUT) ;    
}

void loop() {
  x_pos = analogRead (x_key) ;  
  y_pos = analogRead (y_key) ;
  dir[0] = x_pos;
  dir[1] = y_pos;   
  radio.write(&dir, sizeof(dir));

  Serial.print(x_pos);
  Serial.print(" ");
  Serial.println(y_pos);
}