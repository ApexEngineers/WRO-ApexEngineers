import cv2
import serial
import time
import numpy as np

# Setup the serial communication with Arduino
arduino = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
time.sleep(2)  # Give the connection a second to settle

# Define color ranges for red, green, and pink in HSV
red_lower = (0, 50, 50)
red_upper = (10, 255, 255)
green_lower = (35, 50, 50)
green_upper = (85, 255, 255)
pink_lower = (145, 50, 50)
pink_upper = (165, 255, 255)

# Initialize camera
cap = cv2.VideoCapture(0)

lap_count = 0

def detect_color_and_position(frame):
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    
    # Create masks for red, green, and pink
    mask_red = cv2.inRange(hsv, red_lower, red_upper)
    mask_green = cv2.inRange(hsv, green_lower, green_upper)
    mask_pink = cv2.inRange(hsv, pink_lower, pink_upper)

    # Check for red
    if cv2.countNonZero(mask_red) > 0:
        M = cv2.moments(mask_red)
        if M['m00'] > 0:
            cx_red = int(M['m10'] / M['m00'])
            return 'RED', cx_red
    elif cv2.countNonZero(mask_green) > 0:
        M = cv2.moments(mask_green)
        if M['m00'] > 0:
            cx_green = int(M['m10'] / M['m00'])
            return 'GREEN', cx_green
    elif cv2.countNonZero(mask_pink) > 0:
        return 'PINK', None
    return None, None

def calculate_angular_displacement(color_position, frame_width):
    center_x = frame_width // 2
    displacement = (color_position - center_x) / center_x  # Normalize displacement
    return displacement

while True:
    ret, frame = cap.read()
    if not ret:
        break

    detected_color, color_position = detect_color_and_position(frame)

    # Simulate getting distance from an ultrasonic sensor
    distance = 50  # Placeholder for actual distance measurement

    if lap_count < 3:
        if detected_color == 'RED':
            if color_position is not None:
                displacement = calculate_angular_displacement(color_position, frame.shape[1])
                arduino.write(f'RIGHT {displacement:.2f} {distance}\n'.encode())  # Send right turn signal with displacement and distance
        elif detected_color == 'GREEN':
            if color_position is not None:
                displacement = calculate_angular_displacement(color_position, frame.shape[1])
                arduino.write(f'LEFT {displacement:.2f} {distance}\n'.encode())   # Send left turn signal with displacement and distance
    else:
        # If 3 laps completed, check for pink blocks to initiate parallel parking
        if detected_color == 'PINK':
            arduino.write(b'PARK\n')   # Signal for parallel parking logic

    # Display the camera feed
    cv2.imshow("Frame", frame)

    # Check for quitting the program
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Cleanup
cap.release()
cv2.destroyAllWindows()

cv2.destroyAllWindows()
