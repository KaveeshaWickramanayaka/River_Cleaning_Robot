#include <NewPing.h>

// --- Motor Pins (L298N Driver) ---
#define LEFT_MOTOR_FORWARD 7
#define LEFT_MOTOR_BACKWARD 6
#define RIGHT_MOTOR_FORWARD 5
#define RIGHT_MOTOR_BACKWARD 4

// --- Ultrasonic Sensor ---
#define TRIG_PIN A1
#define ECHO_PIN A2
#define MAX_DISTANCE 200
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

// --- Buzzer ---
#define BUZZER_PIN 3

// --- Shovel Motor Pins ---
#define SHOVEL_PIN1 11
#define SHOVEL_PIN2 12

// --- Debris Detection Range ---
#define DEBRIS_RANGE 20

void setup() {
  setupMotors();
  setupShovel();
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(9600);

  driveForward(); 
}

void loop() {
  int dist = measureDistance();
  Serial.print("Distance: ");
  Serial.println(dist);

  if (dist > 0 && dist <= DEBRIS_RANGE) {
    buzz();
    driveForward();
    delay(1500);
    halt();

    lift();
    delay(2000);
    lower();
    delay(2000);

    driveForward();
  } else {
    driveForward();
  }

  delay(200);
}

// --- Setup Functions ---
void setupMotors() {
  pinMode(LEFT_MOTOR_FORWARD, OUTPUT);
  pinMode(LEFT_MOTOR_BACKWARD, OUTPUT);
  pinMode(RIGHT_MOTOR_FORWARD, OUTPUT);
  pinMode(RIGHT_MOTOR_BACKWARD, OUTPUT);
}

void setupShovel() {
  pinMode(SHOVEL_PIN1, OUTPUT);
  pinMode(SHOVEL_PIN2, OUTPUT);
}

// --- Movement Functions ---
void driveForward() {
  digitalWrite(LEFT_MOTOR_FORWARD, HIGH);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  digitalWrite(RIGHT_MOTOR_FORWARD, HIGH);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
}

void driveBackward() {
  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
  digitalWrite(LEFT_MOTOR_BACKWARD, HIGH);
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, HIGH);
}

void rotateLeft() {
  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
  digitalWrite(LEFT_MOTOR_BACKWARD, HIGH);
  digitalWrite(RIGHT_MOTOR_FORWARD, HIGH);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
}

void rotateRight() {
  digitalWrite(LEFT_MOTOR_FORWARD, HIGH);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, HIGH);
}

void halt() {
  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
}

// --- Shovel Functions ---
void lift() {
  digitalWrite(SHOVEL_PIN1, HIGH);
  digitalWrite(SHOVEL_PIN2, LOW);
  delay(800);
  stopShovel();
}

void lower() {
  digitalWrite(SHOVEL_PIN1, LOW);
  digitalWrite(SHOVEL_PIN2, HIGH);
  delay(800);
  stopShovel();
}

void stopShovel() {
  digitalWrite(SHOVEL_PIN1, LOW);
  digitalWrite(SHOVEL_PIN2, LOW);
}

// --- Buzzer ---
void buzz() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(300);
  digitalWrite(BUZZER_PIN, LOW);
}

// --- Ultrasonic ---
int measureDistance() {
  delay(70);
  int cm = sonar.ping_cm();
  return (cm == 0) ? 250 : cm;
}