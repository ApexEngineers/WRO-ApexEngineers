#include <Servo.h>

// Pin definitions
#define SERVO_PIN 9
#define MOTOR_IN1 10
#define MOTOR_IN2 11
#define MOTOR_ENA 12
#define ULTRASONIC_LEFT_TRIGGER 4
#define ULTRASONIC_LEFT_ECHO 5
#define ULTRASONIC_RIGHT_TRIGGER 6
#define ULTRASONIC_RIGHT_ECHO 7

Servo steeringServo;
int flag = 0;
bool no_detection_lap = false;
int x=0;

void setup() {
  Serial.begin(9600);
  steeringServo.attach(SERVO_PIN);

  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  pinMode(MOTOR_ENA, OUTPUT);

  pinMode(ULTRASONIC_LEFT_TRIGGER, OUTPUT);
  pinMode(ULTRASONIC_LEFT_ECHO, INPUT);
  pinMode(ULTRASONIC_RIGHT_TRIGGER, OUTPUT);
  pinMode(ULTRASONIC_RIGHT_ECHO, INPUT);
}

void loop1(){
  // Check for serial data from Raspberry Pi
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');
    handleData(data);
  }
}

void loop() {

  // If no red or green detected for 1 lap, set no_detection_lap to true
  if (flag == 4 && x==0) {

    no_detection_lap = true;
  }

  // If no detection in 1 lap, skip searching for pink
  else if (no_detection_lap && flag == 24) {
    // Do not search for pink
    stopRobot();
    return;
  }


  // Check ultrasonic sensors for distance and move accordingly
  float leftDistance = getUltrasonicDistance(ULTRASONIC_LEFT_TRIGGER, ULTRASONIC_LEFT_ECHO);
  float rightDistance = getUltrasonicDistance(ULTRASONIC_RIGHT_TRIGGER, ULTRASONIC_RIGHT_ECHO);

  if (leftDistance > 100) {
    flag++;
    turnLeft();
  } else if (rightDistance > 100) {
    flag++;
    turnRight();
  }

  // If flag == 12 and no detection lap is false, do parallel parking
  else if (!no_detection_lap && flag == 12) {
    parallelParking();
    stopRobot();
  }

    // If no obstacles detected, move forward
  else {
    moveForward();
  }
}

// Handle data received from Raspberry Pi
void handleData(String data) {
  if (data.startsWith("RED")) {
    // Parse the distance and angle for red block
    float distance = data.substring(4, data.indexOf(',')).toFloat();
    float angle = data.substring(data.indexOf(',') + 1).toFloat();
    moveRight(angle, distance);
    x=x+1;
  } else if (data.startsWith("GREEN")) {
    // Parse the distance and angle for green block
    float distance = data.substring(6, data.indexOf(',')).toFloat();
    float angle = data.substring(data.indexOf(',') + 1).toFloat();
    moveLeft(angle, distance);
    x=x+1;
  } else if (data.startsWith("PINK")) {
    // Parse the distance and angle for pink block
    float distance = data.substring(5, data.indexOf(',')).toFloat();
    float angle = data.substring(data.indexOf(',') + 1).toFloat();
    parallelParking();
  }
}

// Robot movement functions
void moveForward() {
  Serial.println("Move forward");
  digitalWrite(MOTOR_IN1, HIGH);
  digitalWrite(MOTOR_IN2, LOW);
  analogWrite(MOTOR_ENA, 255); // Full speed
  //delay if not working
}

void turnLeft() {
  Serial.println("Turn left") ;
  steeringServo.write(135); // Turn left
  delay(150);
  digitalWrite(MOTOR_IN1, HIGH);
  digitalWrite(MOTOR_IN2, LOW);
  analogWrite(MOTOR_ENA, 200); // slower speed
  delay(400); //adjust this   --- > for perfect 90 
  steeringServo.write(90); // Straighten up
  delay(150);
  analogWrite(MOTOR_ENA, 0); // Stop motor
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, LOW);
  flag++;
}

void turnRight() {
  Serial.println("Turn right") ;
  steeringServo.write(45); // Turn right
  delay(150);
  digitalWrite(MOTOR_IN1, HIGH);
  digitalWrite(MOTOR_IN2, LOW);
  analogWrite(MOTOR_ENA, 200); // slower speed
  delay(150); // adjust this  ---> for perfect turn
  steeringServo.write(90); // Straighten up
  delay(150);
  analogWrite(MOTOR_ENA, 0); // Stop motor
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, LOW);
  flag++;
}


void moveRight(int angle, int distance) {
  // Adjust movement based on received angle/distance
  Serial.println("RED") ;
  steeringServo.write(angle+15); // Turn right
  delay(150);
  digitalWrite(MOTOR_IN1, HIGH);
  digitalWrite(MOTOR_IN2, LOW);
  analogWrite(MOTOR_ENA, 200); // Full speed
  delay(500); //adjust this 
  steeringServo.write(180-angle-15); // Straighten up
  delay(150);
  analogWrite(MOTOR_ENA, 0); // Stop motor
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, LOW);
  delay(150);
  moveForward();
}

void moveLeft(int angle, int distance) {
  // Adjust movement based on received angle/distance
  Serial.println("GREEN") ;
  steeringServo.write(90-angle+15); // Turn right
  delay(150);
  digitalWrite(MOTOR_IN1, HIGH);
  digitalWrite(MOTOR_IN2, LOW);
  analogWrite(MOTOR_ENA, 200); // Full speed
  delay(500); //adjust this 
  steeringServo.write(angle+15); 
  delay(150); // Straighten up
  analogWrite(MOTOR_ENA, 0); // Stop motor
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, LOW);
  delay(150);
  moveForward();
}

float getUltrasonicDistance(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;
  return distance;
}

void parallelParking() {
  Serial.println("Parking");

}

void stopRobot() {
  Serial.println("Robot stopped") ;
  analogWrite(MOTOR_ENA, 0); // Stop motor
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, LOW);
  delay(100000);
}
