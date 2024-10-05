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
    As a maker, I pride myself on being able to take an idea and turn it into a tangible reality. With skills encompassing various disciplines, from programming to woodworking, I bring versatility to the creative process.

    
 ## Abhiram Alluri 
 	Abhiram Alluri, aged 16, is a passionate individual who loves cricket, software, and physics. He recently did an internship at IIIT under Anuradha Ma’am, where he learned about technology. Abhiram has achieved remarkable success. In 2022, he won first place in the Pravaha Hackathon, beating participants from Russia. He also excelled in robotics, winning the Connect Award at FTC 2024 and earning a chance to represent his team in Australia.

 ## Akhila Alluri
 Akhila Alluri, aged 14, is interested in languages, hardware, and table tennis. She has achieved success both in sports and technology. Akhila placed second in a team table tennis competition at the state level. She also came in second in the FLL (First Lego League) competition in South India, demonstrating her skills in robotics. Akhila´s curiosity extends to languages and hardware as well.

 ## Mehaan Jain
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
