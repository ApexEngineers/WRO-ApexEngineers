![image](https://github.com/user-attachments/assets/b2506d6d-198f-4292-959a-80ea138a93a4)
***

# Contents
* [Hardware](#hardware)
    * [Assembly Instructions & Diagrams](#assembly.md)
    * [Photos](#photos)
* [Uploading Programs](#uploading-programs)
* [Software](#software-documentation)
    * [Operating System](#operating-system)
    * [Programming Language](#programming-language)
    * [Code Documentation](#code-documentation)
* [Team Photos](#team-photos)
* [Demonstrations](#demonstration-video)
* [LiPo Battery Safety Notice](#lipo-battery-safety-notice)



***

# HARDWARE

## ASSEMBLY

Shortened assembly instructions:
1. Print 3D parts
2. Assemble rear axle
3. Solder electronics
4. Assemble steering mechanism
5. Attach main platform
6. Attach electronics
7. Attach upper platform

#### **For an actual build guide, go to [Assembly.md](./assembly.md)**

Here is a simple schematic for how the electronics are wired:

![Wiring schematic](./Schematics/Schematic.png)

## Photos
|                                |                                  |
| ------------------------------ | -------------------------------- |
| ![front](./Vehicle%20Photos/front.jpg) | ![back](./Vehicle%20Photos/back.jpg)     |
| ![left](./Vehicle%20Photos/left.jpg)   | ![right](./Vehicle%20Photos/right.jpg)   |
| ![top](./Vehicle%20Photos/top.jpg)     | ![bottom](./Vehicle%20Photos/bottom.jpg) |

***

# Uploading Programs

Make sure that you have gone through the raspberry pi setup and installed the required libraries like cv2. A detailed explination on installing the libararies can be found
 ([here](./assembly.md#board-setup))**Do not delete the previous directory; you will have to re-install packages!**

***

# Software Documentation

## Operating System

We used the Raspbian operating system, which is Raspberry Pi's official operating system. We also added a startup script ([here](./assembly.md#board-setup)) to run the program on startup.

***

## Programming Language

Our code is in Python (for Raspberry PI) and C++ (for Arduino)

Dependencies:
In Raspberry Pi
* numpy
* cv2
In Arduino
* Servo
* wire

The entire program has been uploaded and must be loaded properly to ensure smooth functioning. 

***


# Team Photos

![Team Photo](./Team%20Photos/Team%20Image.jpg)
![Funny](./Team%20Photos/Funny%20Image.jpg)

***

## Code Documentation

See [CodeDocumentation.md](./CodeDocumentation.md).

***


# LiPo Battery Safety Notice

Although LiPo batteries are one of the safest options for portable, affordable, high-density energy storage, certain precautions are still necessary when handling them. Lithium, being a highly reactive element, can react with moisture in the air if exposed.

Key precautions include:
- Avoid puncturing, deforming, short-circuiting, or heating LiPo batteries above 26°C (80°F).
- Store and charge LiPo batteries in fireproof containers, away from flammable materials and water.
- NEVER charge a swollen or damaged battery (e.g., damaged wires, swelling, or punctured wrapping).
- NEVER leave a charging battery unattended.
- Only use chargers specifically designed for LiPo batteries.
- Dropping a battery can cause damage, potentially rupturing a cell and leading to short circuits.
- Overdischarging a LiPo battery can result in irreversible damage.
- If a LiPo battery falls below its minimum voltage (as indicated in the manual or 3.3V per cell in series), it may suffer internal damage that isn’t immediately visible, which can later lead to swelling, rupture, or even a FIRE.

Always review the safety guidelines and instructions provided with LiPo batteries before use.

### For a more detailed LiPo safety manual there is one on [Safety manual for LiPo Battery](https://www.ehs.washington.edu/system/files/resources/lithium-battery-safety.pdf)
