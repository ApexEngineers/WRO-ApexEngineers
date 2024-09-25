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
int color_count = 0;
bool parking_mode = false;

// MPU6050 Setup (for direction and lap counting)
Adafruit_MPU6050 mpu;
float initial_heading = 0;
float current_heading = 0;

// Ultrasonic Sensor Setup (for parking distance)
Ultrasonic ultrasonic(7, 8);  // Trigger pin 7, Echo pin 8

// TCS3200 Color Sensor Setup (for detecting blue and orange lines)
int s2 = 4; // S2 pin of TCS3200
int s3 = 5; // S3 pin of TCS3200
int outPin = 6; // Output pin of TCS3200

// Movement variables
int speed = 150;  // Speed for the DC motor

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
  // Wait for the start button
  if (digitalRead(buttonPin) == HIGH) {
    if (!parking_mode) {
      // Color sensor detects blue/orange lines for turning
      int detectedColor = detectColor();
      if (detectedColor == 1) {
        turnLeft();  // Blue then orange - turn left
      } else if (detectedColor == 2) {
        turnRight(); // Orange then blue - turn right
      }

      // Handle Raspberry Pi commands
      if (Serial.available()) {
        String command = Serial.readStringUntil('\n');
        if (command == "LEFT") {
          turnLeft();
        } else if (command == "RIGHT") {
          turnRight();
        } else if (command == "PARK") {
          parking_mode = true;
          initiateParking();
        } else if (command == "STOP") {
          stopMotor();
        }
      }
    }

    // Lap count logic using MPU6050 magnetometer
    updateLapCount();

    // Switch to parking mode after 3 laps
    if (lap_count == 3 && !parking_mode) {
      parking_mode = true;
    }
  }
}

// TCS3200 Color Sensor Function
int detectColor() {
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  int blueFrequency = pulseIn(outPin, LOW);

  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  int orangeFrequency = pulseIn(outPin, LOW);

  if (blueFrequency < 20 && orangeFrequency > 30) {
    return 1;  // Blue then orange - turn left
  } else if (orangeFrequency < 20 && blueFrequency > 30) {
    return 2;  // Orange then blue - turn right
  }
  return 0;  // No pattern detected
}

// Ultrasonic Sensor Function for Parking
void initiateParking() {
  while (true) {
    int distance = ultrasonic.read();
    if (distance < 2) {
      stopMotor();  // Stop the vehicle
      break;
    }
    moveForwardSlow();  // Move slowly for parking
  }
}

// Lap Count using MPU6050 (Magnetometer)
void updateLapCount() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  current_heading = calculateHeading(a);

  // If the current heading is the same as initial, increase lap count
  if (abs(current_heading - initial_heading) < 10) {
    lap_count++;
  }
}

// Calculate heading using accelerometer data
float calculateHeading(sensors_event_t &a) {
  float heading = atan2(a.acceleration.y, a.acceleration.x) * 180 / PI;
  if (heading < 0) {
    heading += 360;
  }
  return heading;
}

// Turn Left Function
void turnLeft() {
  steering.write(45);  // Example left turn angle
  moveForward();  // Move the vehicle forward
  delay(1000);  // Adjust delay to control the duration of the turn
  stopMotor();  // Stop after the turn
}

// Turn Right Function
void turnRight() {
  steering.write(135);  // Example right turn angle
  moveForward();  // Move the vehicle forward
  delay(1000);  // Adjust delay to control the duration of the turn
  stopMotor();  // Stop after the turn
}

// Motor Control Functions
void moveForward() {
  // Set motor direction and speed for forward movement
  digitalWrite(motorDirPin1, HIGH);
  digitalWrite(motorDirPin2, LOW);
  analogWrite(motorPin, speed);
}

void moveBackward() {
  // Set motor direction and speed for backward movement
  digitalWrite(motorDirPin1, LOW);
  digitalWrite(motorDirPin2, HIGH);
  analogWrite(motorPin, speed);
}

void moveForwardSlow() {
  // Move forward slowly for parking maneuvers
  digitalWrite(motorDirPin1, HIGH);
  digitalWrite(motorDirPin2, LOW);
  analogWrite(motorPin, 100);  // Slow speed for parking
}

void stopMotor() {
  // Stop the motor by setting speed to 0
  analogWrite(motorPin, 0);
}
