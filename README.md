# spider-robot-

🕷️ Bio-Inspired Spider Robot

This project focuses on designing and developing a bio-inspired insect-like robot that mimics the behavior of real-world organisms using engineering and AI techniques.

The robot is designed as a 4-legged spider structure and is capable of performing several intelligent tasks, including:

🟢 Walking using coordinated leg movement
🟢 Obstacle avoidance using ultrasonic sensors
🟢 Phototaxis (moving toward light) using a light sensor
🟢 Predator detection using a camera and AI model (YOLO)

The system integrates both hardware and software components:

ESP32 microcontroller with PCA9685 servo driver
12 servo motors for leg movement
Raspberry Pi with camera for vision-based detection
External power system with voltage regulation

For predator detection, a custom dataset was created and trained using YOLO, enabling the robot to recognize a predefined object and respond accordingly.

This project demonstrates the integration of mechanical design, embedded systems, and artificial intelligence to build a functional robotics system.
