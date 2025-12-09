//final integration for all components

#include <Servo.h>

#define trigPin 9
#define echoPin 10

// dc motor pins
int motor1pin1 = 2;
int motor1pin2 = 3;
int motor2pin1 = 4;
int motor2pin2 = 5;

Servo myservo;  

// distance thresholds in cm
const long OBSTACLE_THRESHOLD = 30;  // distance for it to be considered blocked
const long CLEAR_THRESHOLD = 50;     // distance for it to be considered clear
//(can be configured as per preferred)


void setup() {
  // ultrasonic setup
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myservo.attach(11);  // servo is on pin11
  
  // Motor pins setup
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("GDG - Autonomous Obstacle Avoidance Started");
  stopMotors();
}

//function to measure distance
long measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // send a 10us HIGH pulse to the trigger pin
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // measure time taken
  long duration = pulseIn(echoPin, HIGH);
  
  // convert duration to distance in cm (speed of sound assumed to be 340m/s)
  long distance = duration * 0.034 / 2;
  
  return distance;
}

//function to check for distance in the laft, cenetr and right direction
void scanEnvironment() {
  Serial.println("=== Scanning Environment ===");
  
  // move to 0 degrees (left) and measure distance
  myservo.write(0);
  delay(500);
  long distanceLeft = measureDistance();
  Serial.print("Left (0°): ");
  Serial.print(distanceLeft);
  Serial.println(" cm");
  
  // move to 90 degrees (center) and measure distance
  myservo.write(90);
  delay(500);
  long distanceCenter = measureDistance();
  Serial.print("Center (90°): ");
  Serial.print(distanceCenter);
  Serial.println(" cm");
  
  // move to 180 degrees (right) and measure distance
  myservo.write(180);
  delay(500);
  long distanceRight = measureDistance();
  Serial.print("Right (180°): ");
  Serial.print(distanceRight);
  Serial.println(" cm");
  
  // rcentralize servo
  myservo.write(90);
  delay(300);
  
  // decide based on distances
  makeMovementDecision(distanceLeft, distanceCenter, distanceRight);
}

//processing function
void makeMovementDecision(long left, long center, long right) {
  Serial.println("=== Making Movement Decision ===");
  
  // check which directions are clear
  bool leftClear = (left > CLEAR_THRESHOLD);
  bool centerClear = (center > CLEAR_THRESHOLD);
  bool rightClear = (right > CLEAR_THRESHOLD);
  
  Serial.print("Clear paths - Left: ");
  Serial.print(leftClear ? "YES" : "NO");
  Serial.print(", Center: ");
  Serial.print(centerClear ? "YES" : "NO");
  Serial.print(", Right: ");
  Serial.println(rightClear ? "YES" : "NO");
  
  // decision logic
  if (centerClear) {
    // center is clear - go forward
    Serial.println("Decision: CENTER clear - Moving FORWARD");
    moveForward();
    delay(2000);  // move forward for 2 seconds
    stopMotors();
  }
  else if (leftClear && !rightClear) {
    // only left is clear
    Serial.println("Decision: LEFT clear - Turning LEFT");
    turnLeft();
    delay(2000);  // turn left for 2 seconds
    stopMotors();
  }
  else if (rightClear && !leftClear) {
    // only right is clear
    Serial.println("Decision: RIGHT clear - Turning RIGHT");
    turnRight();
    delay(2000);  // turn right for 2 seconds
    stopMotors();
  }
  else if (leftClear && rightClear) {
    // both sides clear, choose one (prefer left)[can be configured]
    Serial.println("Decision: BOTH sides clear - Turning LEFT");
    turnLeft();
    delay(2000);
    stopMotors();
  }
  else {
    // all directions blocked - go backward
    Serial.println("Decision: ALL paths blocked - Moving BACKWARD");
    moveBackward();
    delay(2000);
    stopMotors();
  }
}

// driving functions 
void moveForward() {
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
}

void moveBackward() {
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
}

void turnLeft() {
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
}

void turnRight() {
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
}

void stopMotors() {
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
}

void loop() {
  // scan environment and make movement decision
  scanEnvironment();
  
  // wait before next scan
  Serial.println("--- Waiting before next scan ---");
  delay(1000);
}