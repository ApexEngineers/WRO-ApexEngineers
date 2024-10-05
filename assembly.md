![image](https://github.com/user-attachments/assets/b2506d6d-198f-4292-959a-80ea138a93a4)

***

# Build Guide

This is the build guide for WRO Future Engineers team EARTH ALLIES 2024 solution - ApexBot. It assumes you have necessary tools and miscellaneous materials including but not limited to: screw driver set; a 3D printer; a soldering iron; appropriate wires; drilling machine and the required drill bits; and M3, M4, M5 flat/countersunk screws.

Below is a more-or-less detailed step-by-step guide to recreate ApexBot.

***

# Contents

* [Parts List](#parts-list)
* [Chassis Assembly](#chassis-assembly)
* [Raspberry Pi Setup](#raspberry-pi-setup)
    * [Board Setup](#board-setup)

***

## Parts List

* [Micro HDMI to HDMI](https://www.agarwalelectronics.com/product/micro-hdmi-to-hdmi-cable/)
* 2x [Raspberry Pi 4 4GB](https://www.agarwalelectronics.com/product/raspberry-pi-4-4gb/)
* 2x [L298 Motor Driver](https://www.agarwalelectronics.com/product/l298n-motor-driver-board/)
* [5MP Camera](https://www.agarwalelectronics.com/product/5mp-camera-for-raspberry-pi/)
* 2x [HC SR04 - Ultrasonic Sensor](https://www.agarwalelectronics.com/product/hc-sr04-ultrasonic-sensor-4pin/)
* 2x [64GB SD Card](https://www.amazon.in/s?k=64gb+sd+card%27&adgrpid=1326012629748396&hvadid=82876047563782&hvbmt=be&hvdev=c&hvlocphy=156979&hvnetw=o&hvqmt=e&hvtargid=kwd-82876677182464%3Aloc-90&hydadcr=24350_1971234&tag=msndeskstdin-21&ref=pd_sl_r3hr79sdn_e)
* 4x [65mm Rubber](https://www.agarwalelectronics.com/product/bo-wheel-imported/)
* 20-24 gauge wire
* M3 nylon screws (6mm)
* M3 nylon standoffs (6mm works best)
* M3 nylon nuts
* M3 nuts
* Countersunk, cap head M3 screws (6mm and 8mm work best)


You will need (at least) the following tools:
* 3D printer or access to 3D printing service
* Hex Allen drivers (key or bits)
* Phillips head drivers
* Rotary tool with grinding bit (depending on which version of motor)
* Crimper tool
* Soldering iron

*There may be items not listed that are used in the build guide, we apologize if that happens.*

***

## Chassis Assembly

We got the respective 3D printed parts for our ApexBot. Print out the parts located in `/CAD Files/3D` in their given orientation (they have been oriented for the best print results). The main chassis of the robot is made from rigid PVC sheets and a angle grinder and drilling machine was used to create the frame.

*The diagram for the chassis is available in the 'CAD Files*


## Wiring 

Below is the schematic diagram for the ApexBot. 

![image](https://github.com/user-attachments/assets/d1410b12-4917-4785-b478-b5b2e6da40fe)


We have soldered the wires for ease in connections


***

# Raspberry Pi Setup

## Board Setup
To install **Raspberry Pi OS** and configure your display setup, along with installing **NumPy** and **OpenCV (cv2)**, follow these comprehensive steps. This guide walks you through the entire process from setting up the OS to configuring the display and installing important libraries like NumPy and OpenCV, which are commonly used in computer vision projects.

### 1. **Hardware Preparation**
Start by gathering the necessary components. You'll need:
- Raspberry Pi board
- MicroSD card (16GB+ recommended)
- Monitor with HDMI cable
- Keyboard and mouse
- Power supply
- Optional: USB or Wi-Fi dongle for internet connectivity (if not built-in)

### 2. **Install Raspberry Pi OS**
You can easily install Raspberry Pi OS using the **Raspberry Pi Imager**. Download it from the official [Raspberry Pi website](https://www.raspberrypi.org/software/). Once installed:
- Open Raspberry Pi Imager, select **Raspberry Pi OS (32-bit)** from the options.
- Choose the SD card as the storage medium.
- Click **Write** to flash the OS onto the card.

Once the OS is written, insert the SD card into your Raspberry Pi, connect the monitor, keyboard, and other peripherals, and power it on.

### 3. **Initial Setup**
On the first boot, Raspberry Pi OS will guide you through an initial setup wizard to:
- Select your language and keyboard layout.
- Set up Wi-Fi and update the system.
- Set a new password for your user account.

Ensure your Pi is connected to the internet either via Ethernet or Wi-Fi for future package installations.

### 4. **Display Configuration**
By default, Raspberry Pi OS should detect and configure the display. However, if the display isn't set up properly:
- Open the **Raspberry Pi Configuration** tool (found under Preferences).
- Navigate to the **Display** tab to manually set the resolution.

If you face display issues (e.g., blank screen or incorrect resolution), you may need to edit the `config.txt` file. This file contains settings for HDMI and overscan, found in the `/boot` directory. Open the terminal and run:

```bash
sudo nano /boot/config.txt
```

Adjust settings like `hdmi_group` and `hdmi_mode` to match your display’s specifications, then reboot the system.

### 5. **Update Your System**
Before installing any libraries, update your system to ensure compatibility with the latest versions. Open the terminal and run:

```bash
sudo apt update
sudo apt full-upgrade
```

This updates all installed packages and the Raspberry Pi OS itself.

### 6. **Install NumPy**
NumPy is a fundamental library for numerical computations in Python. To install NumPy, use the following command:

```bash
sudo apt install python3-numpy
```

This installs NumPy, allowing you to perform array operations and other numerical computations, which are often essential in robotics and computer vision projects.

### 7. **Install OpenCV (cv2)**
OpenCV is a popular library used for image and video processing. It's essential for tasks like object detection and tracking in computer vision projects.

First, install the required dependencies:

```bash
sudo apt install libopencv-dev python3-opencv
```

To confirm the installation, open a Python session in the terminal:

```bash
python3
```

Then import OpenCV:

```python
import cv2
```

If no errors appear, OpenCV is successfully installed.

### 8. **Setting Up Automatic Startup (Optional)**
If you want your project or program to start automatically on boot, you can configure it by adding a script to the autostart file or setting up a cron job.

To add a Python script to autostart, create a desktop entry:

```bash
nano ~/.config/autostart/myprogram.desktop
```

Then add the following lines:

```
[Desktop Entry]
Name=My Program
Exec=python3 /path/to/your/script.py
Type=Application
```

Save and close the file. This will run the script automatically on boot.

### 9. **Finalizing and Testing**
After installing the libraries, run a test to ensure everything is working:
- Test NumPy by running a simple array operation.
- Test OpenCV by capturing an image from the camera (if available) and displaying it.

You can do this in Python by running:

```python
import numpy as np
import cv2

# Test NumPy
arr = np.array([1, 2, 3])
print(arr)

# Test OpenCV (Capture an image from the camera)
cap = cv2.VideoCapture(0)
ret, frame = cap.read()
cv2.imshow('Frame', frame)
cv2.waitKey(0)
cap.release()
cv2.destroyAllWindows()
```

If you see the image on the screen, OpenCV is properly installed and functional. You're now ready to work on projects that involve video processing and numerical operations on your Raspberry Pi!

### Conclusion
By following these steps, you’ve installed Raspberry Pi OS, configured your display settings, and set up critical libraries like NumPy and OpenCV. This setup is ideal for working on robotics or computer vision projects, as Raspberry Pi combined with Python and OpenCV offers a powerful environment for developing real-time applications. For more details and additional configuration options, you can always refer to [RaspberryTips](https://raspberrytips.com/install-raspberry-pi-os/).

