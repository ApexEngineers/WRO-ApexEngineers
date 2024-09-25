#include <Wire.h>
#include <Servo.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

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
float current_heading = 0;

// TCS3200 Color Sensor Setup (for detecting blue and orange lines)
int s2 = 4; // S2 pin of TCS3200
int s3 = 5; // S3 pin of TCS3200
int outPin = 6; // Output pin of TCS3200

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

  // TCS3200 Color sensor setup
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(outPin, INPUT);
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

  // Update lap count
  updateLapCount();
}

// Parse the command string
void parseCommand(String command, float &displacement, float &distance) {
  int firstSpace = command.indexOf(' ');
  int secondSpace = command.indexOf(' ', firstSpace + 1);
  displacement = command.substring(firstSpace + 1, secondSpace).toFloat();
  distance = command.substring(secondSpace + 1).toFloat();
}

// Turn Left Function for Color (Blue Detected)
void turnLeftColor() {
  if (detectColor() == "BLUE") {
    steering.write(45);  // Example left turn angle for blue color
    moveForward(10.0);   // Move forward a short distance
  }
}

// Turn Right Function for Color (Orange Detected)
void turnRightColor() {
  if (detectColor() == "ORANGE") {
    steering.write(135);  // Example right turn angle for orange color
    moveForward(10.0);    // Move forward a short distance
  }
}

// Detect Color using TCS3200 Color Sensor
String detectColor() {
  int redValue = readColorSensor(); // Read the color sensor values
  if (redValue > thresholdValueForBlue) {
    return "BLUE";
  } else if (redValue < thresholdValueForOrange) {
    return "ORANGE";
  }
  return "NONE";
}

// Read the color sensor and return color intensity
int readColorSensor() {
  // Set S2 and S3 for blue color detection
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  delay(100);
  int blue = pulseIn(outPin, HIGH); // Measure blue color intensity

  // Set S2 and S3 for orange color detection
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  delay(100);
  int orange = pulseIn(outPin, HIGH); // Measure orange color intensity

  // Return the higher value between blue and orange for comparison
  return (blue > orange) ? blue : orange;
}

// Turn Left Function for Obstacles using Camera
void turnLeftObstacle() {
  float distance, angle;
  getCameraData(distance, angle); // Get distance and angle from the camera

  if (distance < 10) { // If too close to the obstacle
    steering.write(30);  // Sharp left turn to avoid the obstacle
    moveForward(0.0); // Stop to avoid collision
  } else if (angle < 0) { // If the obstacle is on the right side
    steering.write(90 + abs(angle));  // Adjust to the left based on angle
    moveForward(5.0); // Move forward cautiously
  } else { // Clear path
    steering.write(90); // Go straight
    moveForward(5.0); // Move forward
  }
}

// Turn Right Function for Obstacles using Camera
void turnRightObstacle() {
  float distance, angle;
  getCameraData(distance, angle); // Get distance and angle from the camera

  if (distance < 10) { // If too close to the obstacle
    steering.write(150);  // Sharp right turn to avoid the obstacle
    moveForward(0.0); // Stop to avoid collision
  } else if (angle > 0) { // If the obstacle is on the left side
    steering.write(90 - abs(angle));  // Adjust to the right based on angle
    moveForward(5.0); // Move forward cautiously
  } else { // Clear path
    steering.write(90); // Go straight
    moveForward(5.0); // Move forward
  }
}

// Motor Control Functions
void moveForward(float distance) {
  // Set motor direction and speed for forward movement
  digitalWrite(motorDirPin1, HIGH);
  digitalWrite(motorDirPin2, LOW);
  analogWrite(motorPin, speed);
}

void initiateParking() {
  // This function is left empty; implement parking logic as needed
}

void stopMotor() {
  // Stop the motor by setting speed to 0
  analogWrite(motorPin, 0);
}

// Function to update lap count using MPU6050 (Magnetometer)
void updateLapCount() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  current_heading = calculateHeading(a);

  // If the current heading is within a certain range of the initial heading, increase lap count
  if (abs(current_heading - initial_heading) < 10) {
    lap_count++;
    Serial.print("Lap Count: ");
    Serial.println(lap_count);
  }
}

// Calculate heading using accelerometer data
float calculateHeading(sensors_event_t &a) {
  // Implement heading calculation based on accelerometer data
  // This is a placeholder function; the actual implementation will depend on your specific needs
  return atan2(a.acceleration.y, a.acceleration.x) * 180 / PI;
}

