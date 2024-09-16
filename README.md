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

Make sure you have gone through the [Raspberry Pi Setup](./assembly.md#jetson-nano-setup) steps and set your static IP, have some form of sshfs, and created the program directory. To upload the program, simply copy the contents of the "Program" into the remote directory. **Do not delete the previous directory; you will have to re-install packages!**

***

# Software Documentation

## Operating System

We used the Jetson Nano's existing operating system, which is Ubuntu 18.04 with Jetpack. It has been changed to text-only mode to remove the unnecessary GUI. We also added a startup script ([see "Board Setup" in ASSEMBLY.md](./assembly.md#board-setup-sshfs-and-static-ip)) to run the program on startup, which waits for a button press before running the program.

***

## Programming Language

All our code is in python

Dependencies:
* Jetson-GPIO
* jetcam
* numpy
* cv2
* adafruit-servokit
* adafruit-circuitpython-mpu6050
* python-socketio
* math
* asyncio
* typing
* traceback
* os
* base64
* time
* threading

The **entire** `Program` directory must be uploaded in order for the program to run. Ensure the `path` constant in `startup.py` is defined properly.

Example:
    `/home/mihir/Desktop/wro-repo-colab/Code_Main/Program/`

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
