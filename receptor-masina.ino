#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

// Pinii pentru motor
int enablePin1 = 5;
int motorPin1 = 4;
int motorPin2 = 2;
int enablePin2 = 3;
int motorPin3 = 9;
int motorPin4 = 10;

RF24 radio(7, 8); // CE, CSN
Servo myservo;  
int servoAngle;
int motorSpeed;
int dir[2];
const byte address[6] = "00001";

void setup() {

  myservo.attach(6); // Pinul pentru servomotor
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  pinMode(enablePin1, OUTPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

}

void loop() {
  if (radio.available()) {
    radio.read(&dir, sizeof(dir));
    servoAngle = map(dir[0], 0, 1023, 56, 102); // Mapează valoarea pentru unghiul servomotorului
    motorSpeed = map(dir[1], 0, 1023, -255, 255);
  }
  myservo.write(servoAngle);

  if (motorSpeed > 10) { // Dacă joystick-ul este împins în sus (inainte)
    digitalWrite(enablePin1, HIGH);
    digitalWrite(enablePin2, HIGH);
    analogWrite(motorPin1, motorSpeed);
    digitalWrite(motorPin2, LOW);
    analogWrite(motorPin3, motorSpeed);
    digitalWrite(motorPin4, LOW);
  } else if (motorSpeed < -10) { // Dacă joystick-ul este împins în jos (înapoi)
    digitalWrite(enablePin1, HIGH);
    digitalWrite(enablePin2, HIGH);
    analogWrite(motorPin1, 255 + motorSpeed); // Ajustare pentru valoarea negativă
    digitalWrite(motorPin2, HIGH);
    analogWrite(motorPin3, 255 + motorSpeed); // Ajustare pentru valoarea negativă
    digitalWrite(motorPin4, HIGH);
  } else { // Dacă joystick-ul este în poziție neutră
    digitalWrite(enablePin1, LOW);
    digitalWrite(enablePin2, LOW);
  }

}


