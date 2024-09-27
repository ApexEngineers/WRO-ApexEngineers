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

# Known values
block_real_height_cm = 10  # Real height of the block in cm
focal_length = 500  # Example focal length (you need to calibrate this)

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
            pixel_height_red = int(M['m01'] / M['m00'])  # Approximate pixel height of the block
            return 'RED', cx_red, pixel_height_red
    elif cv2.countNonZero(mask_green) > 0:
        M = cv2.moments(mask_green)
        if M['m00'] > 0:
            cx_green = int(M['m10'] / M['m00'])
            pixel_height_green = int(M['m01'] / M['m00'])  # Approximate pixel height of the block
            return 'GREEN', cx_green, pixel_height_green
    elif cv2.countNonZero(mask_pink) > 0:
        return 'PINK', None, None
    return None, None, None

def calculate_angular_displacement(color_position, frame_width):
    center_x = frame_width // 2
    displacement = (color_position - center_x) / center_x  # Normalize displacement
    return displacement

def calculate_distance_to_block(pixel_height):
    # Calculate the distance using the formula
    distance = (block_real_height_cm * focal_length) / pixel_height
    return distance

while True:
    ret, frame = cap.read()
    if not ret:
        break

    detected_color, color_position, pixel_height = detect_color_and_position(frame)

    if pixel_height is not None:
        distance = calculate_distance_to_block(pixel_height)  # Calculate distance based on pixel height

    if lap_count < 3:
        if detected_color == 'RED':
            if color_position is not None:
                displacement = calculate_angular_displacement(color_position, frame.shape[1])
                arduino.write(f'RIGHT {displacement:.2f} {distance:.2f}\n'.encode())  # Send right turn signal with displacement and distance
        elif detected_color == 'GREEN':
            if color_position is not None:
                displacement = calculate_angular_displacement(color_position, frame.shape[1])
                arduino.write(f'LEFT {displacement:.2f} {distance:.2f}\n'.encode())   # Send left turn signal with displacement and distance
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
