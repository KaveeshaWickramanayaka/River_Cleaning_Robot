# River_Cleaning_Robot

A robotics application designed to help clean river surfaces by detecting obstacles and lifting debris using an Arduino Uno-controlled robot.

## 📌 Project Overview

This project demonstrates a simple autonomous **River Cleaning Robot** that:
- Moves forward by default.
- Detects obstacles using an ultrasonic sensor.
- Lifts debris with a servo-controlled shovel arm.
- Uses LED and buzzer alerts during obstacle detection.
- Operates stair-like brushes to sweep waste material.

The robot is powered by an **Arduino Uno** and multiple actuators/sensors to carry out its environmental cleaning task.

---

## 🔧 Components Used

- Arduino Uno
- L298N Motor Driver Module (or motor driver circuit)
- 2x DC Motors (Left and Right Wheels)
- 1x Servo Motor (Shovel Arm)
- Ultrasonic Sensor (HC-SR04)
- LED (Obstacle Indicator)
- Passive Buzzer
- Power Supply (Battery Pack)
- Connecting wires, breadboard, and robot chassis

---

## ⚙️ Features

- **Autonomous Navigation** – Moves forward until an obstacle is detected.
- **Obstacle Detection** – Uses ultrasonic sensor to detect objects within 50 cm.
- **Debris Lifting** – Uses a servo motor to lift and drop the shovel.
- **Brush Mechanism** – Motors rotate brushes to push debris into the shovel.
- **Alerts** – LED lights up and buzzer beeps when an obstacle is detected.

---

## 🧠 How It Works

1. The robot begins moving forward.
2. Constantly monitors distance using the ultrasonic sensor.
3. If an object is detected within 50 cm:
   - It stops, alerts using buzzer and LED.
   - Moves backward briefly.
   - Operates brushes and shovel to remove debris.
4. Resumes forward motion.

---

## 🖥️ Arduino Code

The logic is written in C++ and uploaded to the Arduino Uno using the Arduino IDE. The code is modular and easy to adapt.

You can find the code in the file: `river_cleaning_robot.ino`

---

## 🚀 Getting Started

1. **Assemble the hardware** according to the wiring diagram.
2. **Upload the code** using Arduino IDE.
3. Power the robot with a suitable battery pack.
4. Place it in a safe environment for testing.

---

## 📝 Future Improvements

- Add water sensors for floating waste detection.
- Integrate GPS for tracking.
- Add remote control/manual override.
- Solar-powered battery system.

---

## 📷 Demo & Images

> (Include images or GIFs of the working robot here if available)

---

## 🧑‍💻 Author

**Your Name**  
Robotics & Embedded Systems Enthusiast

---

## 📄 License

This project is open-source and free to use for educational and research purposes.

