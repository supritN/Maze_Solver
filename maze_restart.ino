#include <AFMotor.h>

// ---------------- MOTORS ----------------
AF_DCMotor leftMotor(1);    
AF_DCMotor rightMotor(4);

// ---------------- ULTRASONIC PINS ----------------
#define trigLeft   A0
#define echoLeft   A1
#define trigFront  A2
#define echoFront  A3
#define trigRight  A4
#define echoRight  A5

// ---------------- CONSTANTS ----------------
#define BASE_SPEED        85
#define CORRECT_SPEED    75
#define TURN_SPEED       75

#define FRONT_WALL_DIST  15   // cm (front safety)
#define SIDE_WALL_DIST   26   // cm (side wall detection)

#define JUNCTION_ADVANCE 180  // ms

// ---------------- FUNCTION PROTOTYPES ----------------
long readDistance(int trigPin, int echoPin);
void moveForward();
void moveForwardCorrect(long leftDist, long rightDist);
void postTurnCentering();
void turnLeft();
void turnRight();
void turnBack();
void stopMotors();

// ---------------- SETUP ----------------
void setup() {
  pinMode(trigLeft, OUTPUT);
  pinMode(echoLeft, INPUT);
  pinMode(trigFront, OUTPUT);
  pinMode(echoFront, INPUT);
  pinMode(trigRight, OUTPUT);
  pinMode(echoRight, INPUT);

  stopMotors();
  delay(2000);
}

// ---------------- MAIN LOOP ----------------
void loop() {

  long leftDist  = readDistance(trigLeft, echoLeft);
  long frontDist = readDistance(trigFront, echoFront);
  long rightDist = readDistance(trigRight, echoRight);

  // LEFT-HAND RULE WITH SAFE CORRIDOR CONTROL

  // LEFT GAP
  if (leftDist > SIDE_WALL_DIST) {
    moveForward();
    delay(JUNCTION_ADVANCE);
    turnLeft();
    postTurnCentering();
  }

  // STRAIGHT CORRIDOR → apply centering
  else if (frontDist > FRONT_WALL_DIST &&
           leftDist <= SIDE_WALL_DIST &&
           rightDist <= SIDE_WALL_DIST) {

    moveForwardCorrect(leftDist, rightDist);
  }

  // FRONT OPEN (no centering)
  else if (frontDist > FRONT_WALL_DIST) {
    moveForward();
  }

  // RIGHT TURN
  else if (rightDist > SIDE_WALL_DIST) {
    turnRight();
    postTurnCentering();
  }

  // DEAD END
  else {
    turnBack();
    postTurnCentering();
  }
}

// ---------------- FUNCTIONS ----------------

// Ultrasonic distance reading
long readDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 25000);
  long distance = duration * 0.034 / 2;

  if (distance == 0) distance = 100;
  return distance;
}

// Normal forward motion
void moveForward() {
  leftMotor.setSpeed(BASE_SPEED);
  rightMotor.setSpeed(BASE_SPEED);
  leftMotor.run(FORWARD);
  rightMotor.run(FORWARD);
  delay(120);
}

// Corridor-safe forward motion with correction
void moveForwardCorrect(long leftDist, long rightDist) {

  if (leftDist < rightDist) {
    // Too close to left wall
    leftMotor.setSpeed(BASE_SPEED);
    rightMotor.setSpeed(CORRECT_SPEED);
  }
  else if (rightDist < leftDist) {
    // Too close to right wall
    leftMotor.setSpeed(CORRECT_SPEED);
    rightMotor.setSpeed(BASE_SPEED);
  }
  else {
    leftMotor.setSpeed(BASE_SPEED);
    rightMotor.setSpeed(BASE_SPEED);
  }

  leftMotor.run(FORWARD);
  rightMotor.run(FORWARD);
  delay(120);
}

// Apply centering immediately after turns
void postTurnCentering() {
  for (int i = 0; i < 5; i++) {   // ~600 ms centering
    long leftDist  = readDistance(trigLeft, echoLeft);
    long rightDist = readDistance(trigRight, echoRight);

    if (leftDist <= SIDE_WALL_DIST && rightDist <= SIDE_WALL_DIST) {
      moveForwardCorrect(leftDist, rightDist);
    } else {
      moveForward();
    }
  }
}

// Turns
void turnLeft() {
  leftMotor.setSpeed(TURN_SPEED);
  rightMotor.setSpeed(TURN_SPEED);
  leftMotor.run(BACKWARD);
  rightMotor.run(FORWARD);
  delay(350);
  stopMotors();
}

void turnRight() {
  leftMotor.setSpeed(TURN_SPEED);
  rightMotor.setSpeed(TURN_SPEED);
  leftMotor.run(FORWARD);
  rightMotor.run(BACKWARD);
  delay(350);
  stopMotors();
}

void turnBack() {
  leftMotor.setSpeed(TURN_SPEED);
  rightMotor.setSpeed(TURN_SPEED);
  leftMotor.run(FORWARD);
  rightMotor.run(BACKWARD);
  delay(700);
  stopMotors();
}

// Stop motors
void stopMotors() {
  leftMotor.run(RELEASE);
  rightMotor.run(RELEASE);
  delay(40);
}
