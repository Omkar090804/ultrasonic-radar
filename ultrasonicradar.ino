#include <Servo.h>

Servo myServo;
int trigPin = 7; // Trigger pin
int echoPin = 6; // Echo pin 
long duration;
int distance;

void setup() {
  Serial.begin(9600);
  myServo.attach(9); // servo is connected to pin 9
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  for (int angle = 0; angle <= 180; angle += 10) { // 0 to 180 degrees
    myServo.write(angle);
    delay(500); 
    
    distance = getDistance();

    Serial.print(angle);
    Serial.print(",");
    Serial.println(distance);
  }
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; //distance in cm
  return distance;
}
