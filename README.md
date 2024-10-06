![image](https://github.com/user-attachments/assets/b2506d6d-198f-4292-959a-80ea138a93a4)
***

# Contents
* [Hardware](#hardware)
    * [Assembly Instructions & Diagrams](#assembly-instructions)
    * [Schematic Diagram](#schematic-diagram)
    * [Photos of the Robot](#photos-of-the-robot)
* [The Team](#the-team)
* [Software](#software-documentation)
    * [Operating System](#operating-system)
    * [Programming Language](#programming-language)
    * [Code Documentation](#code-documentation)
* [Demonstrations](#demonstration-video)
* [Mobility Management](mobility-management)
* [Obstacle Management](obstacle-management)
* [Power Sense Management](#power-sense-management)
* [LiPo Battery Safety Notice](#lipo-battery-safety-notice)



***
# HARDWARE ASSEMBLY  

## Assembly Instructions
Here’s a detailed overview of the hardware assembly process for your robotics project, following the shortened instructions. This guide includes steps such as preparing the 3D parts, assembling the electronics, and ensuring proper mounting. Please refer to [Assembly.md](./assembly.md) for a more comprehensive guide, but here’s the core outline:

1. **Print 3D Parts**  
   Begin by 3D printing all the necessary parts based on the design files provided. These parts typically include the chassis, rear axle mounts, motor mounts, steering components, and other structural elements. Ensure you use a durable filament such as PLA or ABS for stability, especially since this build will experience mechanical stress.

2. **Assemble the Rear Axle**  
   Mount the rear axle using the printed parts. Make sure to align the axle with the motor housing if your setup includes a rear-drive system. Attach the wheels securely, ensuring they rotate freely without friction.

3. **Solder Electronics**  
   Soldering is crucial to ensure reliable connections between the sensors, microcontroller, motors, and other electrical components. Solder the wires to your motor driver, battery connector, servos, color sensors, and any other peripherals that need a permanent connection. Pay special attention to polarity to avoid damaging components.

4. **Assemble the Steering Mechanism**  
   The steering mechanism is typically composed of a servo motor attached to a linkage system, which moves the front wheels left or right. Ensure the servo is mounted securely and that it can turn the wheels to the desired angle without obstruction.

5. **Attach the Main Platform**  
   The main platform serves as the foundation for your robot. Attach this platform to the rear axle assembly and steering mechanism. Ensure it is level and stable, as this will support the electronics and control systems.

6. **Attach Electronics**  
   Securely mount all electronic components, including the Raspberry Pi, Arduino, motor driver, sensors, and wiring. Ensure that the wires are neatly routed to avoid tangling or obstruction during operation. Use zip ties or adhesive pads to hold everything in place.

7. **Attach Upper Platform**  
   The upper platform serves to protect the electronic components from dust or accidental damage. It also provides a surface for mounting additional sensors or hardware if needed. Make sure it is securely fastened and doesn’t interfere with any moving parts.

For further guidance, including specific schematics and illustrations, you can refer to the Assembly.md file, which provides a full step-by-step guide with photos.

## Schematic Diagram
Here is a simple schematic for how the electronics are wired:

![image](https://github.com/user-attachments/assets/723035cc-10ee-4c7d-9646-833954e1d946)

## Photos of the Robot
|                                |                                  |
| ------------------------------ | -------------------------------- |
| ![front](./Vehicle%20Photos/front.jpg) | ![back](./Vehicle%20Photos/back.jpg)     |
| ![left](./Vehicle%20Photos/left.jpg)   | ![right](./Vehicle%20Photos/right.jpg)   |
| ![top](./Vehicle%20Photos/top.jpg)     | ![bottom](./Vehicle%20Photos/bottom.jpg) |

***
#  The Team 


 Our team is made up of talented young individuals with diverse interests and achievements. We are a collaborative and determined team, eager to inspire others with our journey.
 
 ## Coach - Aditya Vynatheya

 
 Aditya Vynatheya, aged 26, inspires students through hands-on learning in robotics and woodworking. With a passion for creativity and innovation, he fosters teamwork and problem-solving skills. He belives in empowering young minds to build, design and explore. He also transforms ideas into reality while intalling confidence and a love for tecnology and robotics into students.
    
 ## Abhiram Alluri 

 ![PXL_20240919_062103840 MP](https://github.com/user-attachments/assets/92a39841-3518-4caa-919d-0cf6cdbf5427)

Abhiram Alluri, aged 16, is a passionate individual who loves cricket, software, and physics. He recently did an internship at IIIT under Anuradha Ma’am, where he learned about technology. Abhiram has achieved remarkable success. In 2022, he won first place in the Pravaha Hackathon, beating participants from Russia. He also excelled in robotics, winning the Connect Award at FTC 2024 and earning a chance to represent his team in Australia.

 ## Akhila Alluri

 ![PXL_20240919_062045377 MP (1)](https://github.com/user-attachments/assets/a43ae593-0bc9-4893-aade-b4c772532004)

 Akhila Alluri, aged 14, is interested in languages, hardware, and table tennis. She has achieved success both in sports and technology. Akhila placed second in a team table tennis competition at the state level. She also came in second in the FLL (First Lego League) competition in South India, demonstrating her skills in robotics. Akhila´s curiosity extends to languages and hardware as well.

 ## Mehaan Jain

 ![PXL_20240919_062036273 MP](https://github.com/user-attachments/assets/09049ee9-b273-4327-8ea1-b5e25afa5f0f)

 Mehaan Jain, aged 15, is a versatile team member who enjoys basketball and electronics. He interned at IIIT Hyderabad in the field of advanced technology. During 2023, Mehaan stood first in the IIIT Hackathon, showing off his innovative skills. He also completed an internship at T-Hub with Akshay Deshpande, founder of SwitchEko. Mehaan´s story was even featured in a book called "Airavata," highlighting his dedication. He is active in the Robotics Club at Chirec International School

PHOTOS 
 ***
 

# Software Documentation
Here is an overview of the software used in this project: [CodeDocumentation.md](./CodeDocumentation.md).

## Uploading Programs  
Before uploading the code to your Raspberry Pi and Arduino, ensure that your Raspberry Pi is correctly set up with the necessary libraries installed. Follow the detailed instructions on installing the required software components, such as OpenCV (`cv2`) and Numpy, as outlined in the setup guide. You will need to re-install any libraries if previous directories are deleted accidentally.

Make sure not to delete any critical directories once the setup is complete, as re-installing packages may take additional time and effort. It’s recommended to keep a backup of your environment in case any issues arise. 

## Operating System 
We opted to use the Raspbian operating system, which is the official OS for Raspberry Pi. This lightweight Linux distribution is perfect for robotics applications. Additionally, we configured the Raspberry Pi to run the program at startup by adding a custom startup script. This ensures the robot starts functioning immediately after power-up, without the need for manual intervention.

## Programming Languages
The project utilizes two primary programming languages:
- **Python** (for Raspberry Pi): Used for tasks like computer vision, color detection, and serial communication.
- **C++** (for Arduino): Manages low-level motor control, sensor data processing, and movement logic.

## Dependencies
- **In Raspberry Pi**: 
   - `numpy`: A fundamental package for numerical computing in Python.
   - `cv2`: The Python binding for OpenCV, used for image processing and computer vision tasks.
  
- **In Arduino**: 
   - `Servo`: A library to control the servos in the steering mechanism.
   - `Wire`: Used for I2C communication between various sensors and the Arduino.

Make sure all dependencies are installed correctly for the system to function seamlessly.

# Demonstration Video

# Mobility Management

**Mobility management** is crucial in enabling the robot to move efficiently and respond to environmental changes. The robot's mobility system typically involves **steering**, **driving**, and **speed control**. Here's how these components interact in your project:

#### 1. **DC Motor for Movement**:
- The **DC motor** controls the forward and backward movement of the robot. It is connected to a **motor driver** (likely an H-Bridge) that controls the direction and speed via **PWM (Pulse Width Modulation)**. 
  - **Direction control** is managed by setting the logic for the motor’s IN1 and IN2 pins. 
    - When IN1 = HIGH and IN2 = LOW, the motor rotates forward.
    - When IN1 = LOW and IN2 = HIGH, the motor rotates backward.
  - **Speed control** is achieved by varying the duty cycle of the PWM signal sent to the ENA pin. A higher duty cycle results in faster movement.

#### 2. **Servo Motor for Steering**:
- **Servo motor** is responsible for **steering** the robot. It adjusts the wheels to turn the robot left, right, or keep it moving straight.
  - The servo angle is controlled using the `Servo` library, where:
    - **90°** represents a straight position.
    - **135°** or higher represents a left turn.
    - **45°** or lower represents a right turn.

#### 3. **Turning Logic**:
- **Turning** is handled by controlling the servo motor while the DC motor is running.
  - To **turn left**:
    - The servo motor turns to an angle greater than 90° (e.g., 135°), and the DC motor continues to run at a lower speed for smooth turning.
  - To **turn right**:
    - The servo motor turns to an angle less than 90° (e.g., 45°), with a similar speed adjustment.
  - After a turn, the servo motor is reset to **90°** (straight), and the motor resumes full-speed movement.

#### 4. **Motion Adjustments**:
- Speed can be adjusted dynamically based on environmental conditions, such as detecting obstacles (discussed below) or when precision is required (e.g., during parallel parking).

# Obstacle Management

**Obstacle management** ensures the robot avoids collisions and navigates around obstacles it encounters in its path. Your robot uses a combination of **ultrasonic sensors** and **camera-based color detection** to detect and react to obstacles.

#### 1. **Ultrasonic Sensors for Obstacle Avoidance**:
- **Ultrasonic sensors** are used on both the left and right sides of the robot. They emit sound waves and calculate the distance to an obstacle based on how long the signal takes to return.
  - When the sensor detects an object within a certain threshold distance (e.g., 20-30 cm), the robot decides to turn in the opposite direction to avoid it.
  - **Left-side detection**: If the left ultrasonic sensor detects an obstacle within a set range (e.g., 20 cm), the robot will turn **right**.
  - **Right-side detection**: Similarly, if the right ultrasonic sensor detects an obstacle, the robot will turn **left**.
  
The obstacle detection process is handled via the following logic:
- **Distance Measurement**: The ultrasonic sensor calculates the distance to an obstacle:
  ```cpp
  float distance = duration * 0.034 / 2;
  ```
  - **0.034** is the speed of sound in cm/μs, and dividing by 2 accounts for the round-trip distance.
  
- **Decision-Making**:
  - If the distance is below a certain threshold (e.g., 20 cm), the robot will turn left or right accordingly.

#### 2. **Color-Based Obstacle Detection Using Camera**:
- In addition to ultrasonic sensors, **camera-based detection** via OpenCV identifies colored blocks (red, green, and pink) in the robot's path.
  - **Red and Green Blocks**: These indicate obstacles the robot must avoid.
    - When a **red block** is detected within 40 cm, the robot will turn **right**.
    - When a **green block** is detected, the robot will turn **left**.
  - The **distance to blocks** is calculated using the **height of the block in the camera's frame** and the known height of the block (10 cm in this case). The formula for calculating distance is:
    ```python
    def calculate_distance(pixel_height):
        return (BLOCK_HEIGHT_CM * FOCAL_LENGTH) / pixel_height
    ```
    - Here, the focal length is pre-calibrated, and the pixel height is the size of the block in the camera’s field of view.

#### 3. **Handling Multiple Obstacles**:
- If **multiple obstacles** are detected (e.g., more than one block), the robot processes the **nearest block** first and turns accordingly, ensuring it avoids each obstacle sequentially.


***

# Power Sense Management

**Power sense management** refers to the robot's ability to handle power distribution, monitor power consumption, and ensure all components have the required energy to operate effectively. It involves managing power between the motors, sensors, and the microcontroller (Arduino or Raspberry Pi). Key aspects of power management include:

#### 1. **Battery Management**:
- The robot is likely powered by multiple batteries:
  - **One battery for the motors**: Motors typically require more power, so a dedicated battery ensures they receive consistent voltage without interference from other components.
  - **One battery for the SBC (Single Board Computer) and SBM (Single Board Microcontroller)**: This battery powers the Raspberry Pi and Arduino, ensuring reliable data processing and communication.
  
#### 2. **Power Distribution**:
- A **switch** is used to connect or disconnect the power to the robot’s components.
  - When the switch is turned on, the batteries supply power to all consumers, including the DC motors, servo motor, sensors, and microcontrollers.
  
#### 3. **Voltage Regulation**:
- **Voltage regulators** ensure that components receive the appropriate voltage. Motors and servo motors may require a higher voltage (e.g., 12V), while microcontrollers (e.g., Arduino) need 5V logic.
- Voltage regulation also protects the robot from **power surges** that could damage sensitive components like sensors and microcontrollers. we have used a motor driver for this. 

#### 4. **Motor Power Management**:
- The DC motor's **speed and torque** are controlled via **PWM signals** sent from the Arduino. The `analogWrite()` function adjusts the duty cycle of the PWM to control motor speed:
  ```cpp
  analogWrite(MOTOR_ENA, 255);  // Full speed
  analogWrite(MOTOR_ENA, 200);  // Reduced speed for turning
  analogWrite(MOTOR_ENA, 0);    // Stop the motor
  ```
  - By adjusting the PWM values, the robot can **conserve power** during turns or slow maneuvers, reducing overall power consumption.



# LiPo Battery Safety Notice
LiPo (Lithium Polymer) batteries are widely used in robotics projects due to their high energy density and relatively low cost. However, they require careful handling to avoid dangerous situations, such as fires. Here are some essential precautions to follow when handling LiPo batteries:

- **Avoid Puncturing or Deforming**: Never puncture or deform a LiPo battery. Doing so can cause an internal short circuit, leading to a fire hazard.
  
- **Store in Fireproof Containers**: When not in use or charging, store your LiPo batteries in fireproof containers, away from flammable materials. Avoid exposure to water, as lithium reacts aggressively with moisture.

- **Do Not Charge Swollen or Damaged Batteries**: If your battery shows signs of swelling or has visible damage, such as torn wires or punctured casing, do not attempt to charge it. Swollen batteries can be a sign of internal damage that may lead to an explosion or fire.

- **Never Leave Charging Batteries Unattended**: Always monitor the battery while it’s charging. LiPo batteries can overheat if left charging for too long, which could cause a fire.

- **Use Correct Chargers**: Only use chargers specifically designed for LiPo batteries. Overcharging or using an incorrect charger can damage the battery and increase the risk of a fire.

- **Dropping the Battery**: Dropping a LiPo battery can rupture internal cells or damage protective layers. If you suspect a battery has been dropped or damaged, inspect it thoroughly for swelling or irregularities before use.

- **Avoid Overdischarge**: Discharging a LiPo battery below its minimum voltage (usually around 3.3V per cell) can cause permanent damage. Most electronic speed controllers and power modules have built-in safety features to prevent overdischarging. Always follow these guidelines to extend the life of your LiPo batteries and keep your project safe.

For further details, please consult the detailed safety manual provided with your LiPo battery, which contains additional guidelines and best practices for safe handling. [Safety manual for LiPo Battery](https://www.ehs.washington.edu/system/files/resources/lithium-battery-safety.pdf)
