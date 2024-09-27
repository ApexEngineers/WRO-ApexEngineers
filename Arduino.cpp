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

// Threshold values for color detection
int thresholdValueForBlue = 200;   // You will need to adjust these values based on your sensor readings
int thresholdValueForOrange = 100; // Adjust this based on testing

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
  // Lap counting
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  current_heading = calculateHeading(a);

  if (isLapCompleted(current_heading)) {
    lap_count++;
    Serial.print("LAP ");
    Serial.println(lap_count); // Send lap count to Raspberry Pi
  }

  // Parking mode check
  if (lap_count >= 3 && !parking_mode) {
    initiateParking();
    parking_mode = true;
  }

  // Example: detect colors and move based on detection
  String detectedColor = detectColor();
  if (detectedColor == "BLUE") {
    turnLeftColor();
  } else if (detectedColor == "ORANGE") {
    turnRightColor();
  }
}

// Turn Left Function for Color (Blue Detected)
void turnLeftColor() {
  steering.write(45);  // Example left turn angle for blue color
  moveForward(10.0);   // Move forward a short distance
}

// Turn Right Function for Color (Orange Detected)
void turnRightColor() {
  steering.write(135);  // Example right turn angle for orange color
  moveForward(10.0);    // Move forward a short distance
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

// Move forward function
void moveForward(float distance) {
  // Set motor direction and speed for forward movement
  digitalWrite(motorDirPin1, HIGH);
  digitalWrite(motorDirPin2, LOW);
  analogWrite(motorPin, speed);
}

// Function to calculate heading using MPU6050
float calculateHeading(sensors_event_t &a) {
  // Implement heading calculation based on accelerometer data
  return atan2(a.acceleration.y, a.acceleration.x) * 180 / PI;
}

// Lap completion check based on heading
bool isLapCompleted(float current_heading) {
  return abs(current_heading - initial_heading) >= 360;  // Adjust this condition based on your environment
}

// Parking logic
void initiateParking() {
  Serial.println("Parking Mode Initiated");
  steering.write(90);  // Straight position for parking
  moveForward(5.0);    // Move forward a short distance
  steering.write(135); // Adjust for parallel parking (right turn)
  moveForward(3.0);    // Complete parking procedure
}
