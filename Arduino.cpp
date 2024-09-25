#include <Wire.h>
#include <Servo.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Ultrasonic.h>

// Servo and Motor setup
Servo steering;
int motorPin = 9;  // DC motor control pin
int motorDirPin1 = 3; // Motor direction pin 1
int motorDirPin2 = 4; // Motor direction pin 2
int buttonPin = 2; // Start button
int lap_count = 0;
bool parking_mode = false;

// MPU6050 Setup (for direction and lap counting)
Adafruit_MPU6050 mpu;
float initial_heading = 0;

// Ultrasonic Sensor Setup (for parking distance)
Ultrasonic ultrasonic(7, 8);  // Trigger pin 7, Echo pin 8

// Movement variables
int speed = 150;  // Speed for the DC motor

// State variables
enum State { IDLE, TURN_LEFT_COLOR, TURN_RIGHT_COLOR, TURN_LEFT_OBSTACLE, TURN_RIGHT_OBSTACLE, PARKING };
State currentState = IDLE;

// Timer variables
unsigned long previousMillis = 0;
const long interval = 100; // Interval for sensor readings and actions

void setup() {
  Serial.begin(9600);  // Initialize Serial communication between Arduino and Raspberry Pi
  Serial.println("Arduino ready.");  // Ready message for Pi
  
  // Servo motor setup
  steering.attach(10);  // Steering servo
  pinMode(motorPin, OUTPUT);
  pinMode(motorDirPin1, OUTPUT);
  pinMode(motorDirPin2, OUTPUT);
  pinMode(buttonPin, INPUT);

  // MPU6050 setup
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  // Set initial heading (direction) from magnetometer
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  initial_heading = calculateHeading(a);
}

void loop() {
  // Check for incoming commands from Raspberry Pi
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    float displacement, distance;

    if (command.startsWith("LEFT_COLOR")) {
      parseCommand(command, displacement, distance);
      currentState = TURN_LEFT_COLOR;
    } else if (command.startsWith("RIGHT_COLOR")) {
      parseCommand(command, displacement, distance);
      currentState = TURN_RIGHT_COLOR;
    } else if (command.startsWith("LEFT_OBSTACLE")) {
      parseCommand(command, displacement, distance);
      currentState = TURN_LEFT_OBSTACLE;
    } else if (command.startsWith("RIGHT_OBSTACLE")) {
      parseCommand(command, displacement, distance);
      currentState = TURN_RIGHT_OBSTACLE;
    } else if (command == "PARK") {
      parking_mode = true;
      currentState = PARKING;
    } else if (command == "STOP") {
      stopMotor();
      currentState = IDLE;  // Switch to IDLE state
    }
  }

  // State management
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    switch (currentState) {
      case TURN_LEFT_COLOR:
        turnLeftColor();
        currentState = IDLE;  // Return to IDLE state after turning
        break;

      case TURN_RIGHT_COLOR:
        turnRightColor();
        currentState = IDLE;  // Return to IDLE state after turning
        break;

      case TURN_LEFT_OBSTACLE:
        turnLeftObstacle();
        currentState = IDLE;  // Return to IDLE state after turning
        break;

      case TURN_RIGHT_OBSTACLE:
        turnRightObstacle();
        currentState = IDLE;  // Return to IDLE state after turning
        break;

      case PARKING:
        initiateParking();
        break;

      case IDLE:
        // Optionally perform other idle tasks here
        break;
    }
  }
}

// Parse the command string
void parseCommand(String command, float &displacement, float &distance) {
  int firstSpace = command.indexOf(' ');
  int secondSpace = command.indexOf(' ', firstSpace + 1);
  displacement = command.substring(firstSpace + 1, secondSpace).toFloat();
  distance = command.substring(secondSpace + 1).toFloat();
}

// Turn Left Function for Color (Square Path)
void turnLeftColor() {
  steering.write(45);  // Example left turn angle for color detection
  moveForward(10.0);   // Move forward a short distance for color detection
  // Add logic to adjust duration or stop based on sensor input if needed
}

// Turn Right Function for Color (Square Path)
void turnRightColor() {
  steering.write(135);  // Example right turn angle for color detection
  moveForward(10.0);    // Move forward a short distance for color detection
  // Add logic to adjust duration or stop based on sensor input if needed
}

// Turn Left Function for Obstacles
void turnLeftObstacle() {
  steering.write(45);  // Example left turn angle for obstacle avoidance
  moveForward(5.0);    // Move forward a short distance to avoid the obstacle
  // Add logic to adjust duration or stop based on sensor input if needed
}

// Turn Right Function for Obstacles
void turnRightObstacle() {
  steering.write(135);  // Example right turn angle for obstacle avoidance
  moveForward(5.0);     // Move forward a short distance to avoid the obstacle
  // Add logic to adjust duration or stop based on sensor input if needed
}

// Motor Control Functions
void moveForward(float distance) {
  // Set motor direction and speed for forward movement
  digitalWrite(motorDirPin1, HIGH);
  digitalWrite(motorDirPin2, LOW);
  analogWrite(motorPin, speed);
}

void initiateParking() {
  int distance = ultrasonic.read();
  if (distance < 2) {
    stopMotor();  // Stop the vehicle
  } else {
    moveForward(0.0);  // Keep moving slowly if no obstacle
  }
}

void stopMotor() {
  // Stop the motor by setting speed to 0
  analogWrite(motorPin, 0);
}

// Function to calculate heading (add implementation if needed)
float calculateHeading(sensors_event_t &a) {
  float heading = atan2(a.acceleration.y, a.acceleration.x) * 180 / PI;
  if (heading < 0) {
    heading += 360;
  }
  return heading;
}

