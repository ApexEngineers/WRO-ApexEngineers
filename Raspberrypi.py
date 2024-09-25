import cv2
import serial
import time

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
color_count = 0

def detect_color(frame):
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    
    # Create masks for red, green, and pink
    mask_red = cv2.inRange(hsv, red_lower, red_upper)
    mask_green = cv2.inRange(hsv, green_lower, green_upper)
    mask_pink = cv2.inRange(hsv, pink_lower, pink_upper)

    # Check for red
    if cv2.countNonZero(mask_red) > 0:
        return 'RED'
    elif cv2.countNonZero(mask_green) > 0:
        return 'GREEN'
    elif cv2.countNonZero(mask_pink) > 0:
        return 'PINK'
    return None

while True:
    ret, frame = cap.read()
    if not ret:
        break

    detected_color = detect_color(frame)

    if lap_count < 3:
        # Send commands based on detected color
        if detected_color == 'RED':
            arduino.write(b'RIGHT\n')  # Send right turn signal to Arduino
        elif detected_color == 'GREEN':
            arduino.write(b'LEFT\n')   # Send left turn signal to Arduino
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
