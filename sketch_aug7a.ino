#include <Servo.h>
const int trigPin = 10;
const int echoPin = 11;
const int ledPins[] = {4, 5, 6, 7};
const int numLeds = 4;
const int distanceThresholds[] = {35, 25, 15, 10}; // Distâncias em cm para acender cada LED

const int buzzer = 12;
Servo servo_13;


// Parte servo motor - segundo sensor ultrassônico
long readUltrasonicDistance(int triggerPin, int echoPin) {

pinMode(triggerPin, OUTPUT);
digitalWrite(triggerPin, LOW);
delayMicroseconds(2);  
digitalWrite(triggerPin, HIGH);
delayMicroseconds(10);
  
digitalWrite(triggerPin, LOW);
pinMode(echoPin, INPUT);
return pulseIn(echoPin, HIGH);
}



void setup() {
  Serial.begin(9600);

//servo motor
servo_13.attach(13, 500, 2500);



  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  // Envia um pulso de 10 microssegundos para o pino TRIG
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Calcula a duração do pulso no pino ECHO
  long duration = pulseIn(echoPin, HIGH);

  // Calcula a distância em centímetros
  float distance = (duration * 0.034) / 2;

  // Imprime a distância no monitor serial
  Serial.print("Distância: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Acende os LEDs conforme a distância
  for (int i = 0; i < numLeds; i++) {
    if (distance < distanceThresholds[i]) {
      digitalWrite(ledPins[i], HIGH);
    } else {
      digitalWrite(ledPins[i], LOW);
    }
  }

  delay(1000);



//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

if (distance < 10) { //Buzzer
	tone(buzzer, 1000); // Send 1KHz sound signal...
    delay(1000);        // ...for 1 sec
    noTone(buzzer);     // Stop sound...
    delay(1000); 
    delay(10);
  } 
  
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  
if (0.01723 * readUltrasonicDistance(3, 2) < 12) { //3 e 2 são as portas do sensor ultrassônico - sensor menor que 13 CM
servo_13.write(120); 
delay(10000);
  } else {
	servo_13.write(0);
	
  
	}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  

  
}
