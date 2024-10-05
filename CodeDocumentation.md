![image](https://github.com/user-attachments/assets/b2506d6d-198f-4292-959a-80ea138a93a4)
***

# Contents
* [Algorithm](#algorithm)
    * [Outline](#general-outline)
    * [Image Processing](#image-processing)
    * [Simple Driver](#simple-driver)
* [Code Structure](#code-structure)

***

# Algorithm

Our program runs a constant update loop. All controller code can be found in `./Program/Controllers/`, and is divided into three main modules: The `preProcessingController`, which pre-process images; `slam`, which is a modified SLAM (Simultaneous Localization and Mapping) algorithm with limited landmark locations; and `controller`, divided into `slamcontroller`, `basiccontroller`

## General Outline
* [Arduino]()
    1. Capture
    2. [Undistort](#undistorting)
    3. [Filter](#filtering)
    4. [Find wall heights](#finding-wall-heights)
    5. [Find contours](#finding-contours)
    6. [Find wall lines](#finding-wall-lines)
    7. [Merge & Convert wall lines and contours](#merge-contours--wall-lines)
* [Simple Driver](#simple-driver)
    1. [Find Car Direction](#finding-car-direction)
    2. [Categorize Walls](#categorizing-walls)
    3. [Filter Traffic Signals](#filtering-traffic-signals)
    4. [Calculate Steering](#calculating-steering)
* SLAM Driver
    1. Non-functional (but if it works it'll be really cool)

***

### Detailed Explanation of the Python Code (Raspberry Pi)

This Python script handles real-time video processing using OpenCV to detect red, green, and pink blocks in a frame captured from a camera. It calculates the distance and angle to the blocks based on their size and position and sends this information to an Arduino for obstacle avoidance and parallel parking.

#### **Imports and Serial Setup**
```python
import cv2
import serial
import time
```
- `cv2`: OpenCV is used for image processing and color detection.
- `serial`: Used for communication with the Arduino through the serial port.
- `time`: Adds delays when necessary, especially for giving the serial connection time to establish.

```python
arduino = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
time.sleep(2)
```
- Establishes a serial connection to the Arduino via `/dev/ttyACM0` at a baud rate of `9600`.
- A delay of `2 seconds` is given to ensure the connection is properly set up.

#### **Constants**
```python
BLOCK_HEIGHT_CM = 10  # The height of the block in cm
FOCAL_LENGTH = 600    # Focal length of your camera, adjust based on testing
block_sent = False    # A flag to prevent sending duplicate data for the same block
```
- `BLOCK_HEIGHT_CM` defines the real-world height of a block (10 cm).
- `FOCAL_LENGTH` is a parameter used to calculate the distance from the camera to the block based on its pixel height.
- `block_sent` ensures data is sent only once per detected block to prevent redundant signals.

#### **Distance Calculation**
```python
def calculate_distance(pixel_height):
    return (BLOCK_HEIGHT_CM * FOCAL_LENGTH) / pixel_height
```
- This function calculates the distance of a block from the camera using the known block height, focal length, and the pixel height of the detected block in the image.

#### **Block Detection**
```python
def detect_block(frame):
    global block_sent
```
- This function processes the camera frame to detect red, green, and pink blocks. It converts the image into the HSV color space, which is more suitable for color segmentation.

- **Color Detection Ranges:**
    - Red blocks are detected within a range of `0-10` in the hue channel.
    - Green blocks are detected within `36-86` hue values.
    - Pink blocks (used for parallel parking) are detected in the range of `140-160` in the hue channel.

- **Creating Color Masks:**
```python
red_mask = cv2.inRange(hsv_frame, red_lower, red_upper)
green_mask = cv2.inRange(hsv_frame, green_lower, green_upper)
pink_mask= cv2.inRange(hsv_frame, pink_lower, pink_upper)
```
- These masks isolate pixels within the specified color ranges.

- **Contours and Block Detection Logic:**
```python
contours_red, _ = cv2.findContours(red_mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
```
- The contours of detected blocks are found, and the largest contour is used to estimate the block's position, size, distance, and angle from the center of the frame.

- **Sending Data to Arduino:**
```python
if not block_sent and distance < 40:
    send_data("RED", distance, angle)
    block_sent = True
```
- If a red or green block is detected within 40 cm, the data is sent to the Arduino using the `send_data` function. For pink blocks (related to parallel parking), data is sent when the block is within 50 cm.

#### **Data Sending Function**
```python
def send_data(color, distance, angle):
    data = f"{color},{distance:.2f},{angle:.2f}\n"
    arduino.write(data.encode())
```
- This function formats the detected block’s color, distance, and angle into a string, which is sent to the Arduino via serial communication.

### Detailed Explanation of the Arduino Code

This Arduino sketch receives commands from the Raspberry Pi and controls the robot’s movement using servos and motors. It also handles ultrasonic sensors for distance measurement and implements parallel parking based on the detection of pink blocks.

#### **Setup and Pin Definitions**
```cpp
#include <Servo.h>

#define SERVO_PIN 9
#define MOTOR_IN1 10
#define MOTOR_IN2 11
#define MOTOR_ENA 12
#define ULTRASONIC_LEFT_TRIGGER 4
#define ULTRASONIC_LEFT_ECHO 5
#define ULTRASONIC_RIGHT_TRIGGER 6
#define ULTRASONIC_RIGHT_ECHO 7
```
- The servomotor, motor pins, and ultrasonic sensor pins are defined.
- The servomotor controls the robot's steering, while the motors control its forward and backward movement.

#### **Ultrasonic Sensor Function**
```cpp
float getUltrasonicDistance(int triggerPin, int echoPin) {
    // Sends a trigger pulse and measures the time taken for the echo to return
    long duration = pulseIn(echoPin, HIGH);
    float distance = duration * 0.034 / 2;
    return distance;
}
```
- This function measures the distance using ultrasonic sensors placed on the left and right sides of the robot.

#### **Block Handling**
The `handleData` function processes serial data from the Raspberry Pi, checking for "RED," "GREEN," and "PINK" block detections. Depending on the color:
- **Red/Green Blocks:** The robot turns right or left and moves forward based on the distance and angle received.
- **Pink Block:** The robot performs parallel parking.

#### **Movement and Steering Functions**
- **`moveForward`**, **`turnLeft`**, **`turnRight`**: Control the robot’s movement, adjusting the speed and direction.
- **`moveLeft`, `moveRight`**: These functions adjust the robot's position based on the received angle and distance from a detected red or green block.

#### **Parallel Parking**
```cpp
void parallelParking() {
    Serial.println("Parking");
    // Implement the logic to turn the robot and position it into the parking space
}
```
- When two pink blocks are detected, the robot initiates parallel parking.

### Parallel Parking Logic
- **Pink block detection (via Raspberry Pi):** Once the Pi detects two pink blocks, it sends a "PINK" signal to the Arduino.
- **Robot Response (Arduino):** The `parallelParking` function would move the robot forward, position it between the blocks, and adjust the steering to park in the available space.

### Improvements & Next Steps:
1. **Parallel Parking Implementation:** The `parallelParking` function needs a detailed implementation of the turning and parking sequence, likely involving multiple servo adjustments and motor control.
2. **Tuning:** Fine-tuning parameters such as the turning angles, delay times, and ultrasonic threshold values will be necessary for smooth operation.

