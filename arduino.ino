#include <Servo.h>

// Motor Pins
const int LEFT_MOTOR_FORWARD = 5;
const int LEFT_MOTOR_BACKWARD = 6;
const int RIGHT_MOTOR_FORWARD = 10;
const int RIGHT_MOTOR_BACKWARD = 11;

// Sensor and Actuator Pins
const int TRIG_PIN = 7;
const int ECHO_PIN = 8;
const int LED_PIN = 13;
const int BUZZER_PIN = 2;
const int SHOVEL_SERVO_PIN = 9;

// Constants
const int MOTOR_SPEED = 255;
const int OBSTACLE_DISTANCE_THRESHOLD = 50;

// Globals
Servo shovelServo;
long duration;
int distance;

void setup() {
  initializeMotors();
  initializeSensors();
  initializeServo();
  Serial.begin(9600);
}

void loop() {
  move(MOVE_FORWARD);

  distance = getDistance();
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance < OBSTACLE_DISTANCE_THRESHOLD) {
    handleObstacle();
  }

  rotateBrushes();
  operateShovel();
}

enum Direction {
  MOVE_FORWARD,
  MOVE_BACKWARD,
  TURN_LEFT,
  TURN_RIGHT,
  STOP
};

void initializeMotors() {
  pinMode(LEFT_MOTOR_FORWARD, OUTPUT);
  pinMode(LEFT_MOTOR_BACKWARD, OUTPUT);
  pinMode(RIGHT_MOTOR_FORWARD, OUTPUT);
  pinMode(RIGHT_MOTOR_BACKWARD, OUTPUT);
}

void initializeSensors() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void initializeServo() {
  shovelServo.attach(SHOVEL_SERVO_PIN);
  shovelServo.write(0);
}

void move(Direction dir) {
  switch (dir) {
    case MOVE_FORWARD:
      analogWrite(LEFT_MOTOR_FORWARD, MOTOR_SPEED);
      analogWrite(RIGHT_MOTOR_FORWARD, MOTOR_SPEED);
      digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
      digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
      break;
    case MOVE_BACKWARD:
      analogWrite(LEFT_MOTOR_BACKWARD, MOTOR_SPEED);
      analogWrite(RIGHT_MOTOR_BACKWARD, MOTOR_SPEED);
      digitalWrite(LEFT_MOTOR_FORWARD, LOW);
      digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
      break;
    case TURN_LEFT:
      analogWrite(LEFT_MOTOR_BACKWARD, MOTOR_SPEED);
      analogWrite(RIGHT_MOTOR_FORWARD, MOTOR_SPEED);
      digitalWrite(LEFT_MOTOR_FORWARD, LOW);
      digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
      break;
    case TURN_RIGHT:
      analogWrite(LEFT_MOTOR_FORWARD, MOTOR_SPEED);
      analogWrite(RIGHT_MOTOR_BACKWARD, MOTOR_SPEED);
      digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
      digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
      break;
    case STOP:
      digitalWrite(LEFT_MOTOR_FORWARD, LOW);
      digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
      digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
      digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
      break;
  }
}

long getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2;
}

void handleObstacle() {
  digitalWrite(LED_PIN, HIGH);
  tone(BUZZER_PIN, 1000, 500);

  move(STOP);
  delay(2000);
  move(MOVE_BACKWARD);
  delay(1000);
}

void rotateBrushes() {
  analogWrite(LEFT_MOTOR_BACKWARD, MOTOR_SPEED);
  analogWrite(RIGHT_MOTOR_BACKWARD, MOTOR_SPEED);
  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
}

void operateShovel() {
  shovelServo.write(90);
  delay(2000);
  shovelServo.write(0);
  delay(2000);
}
