
# Wall-Based Maze Solver Bot

An autonomous wall-following maze-solving robot built using Arduino Uno and three ultrasonic sensors. The robot detects surrounding walls and obstacles, makes real-time navigation decisions, and navigates through a maze without human intervention.

## Project Overview

The robot uses three ultrasonic sensors to detect walls and obstacles in its surroundings. The Arduino Uno processes sensor readings and controls the motors through the L293D motor driver to navigate through the maze using a wall-following algorithm.

## Components Used

| Component | Quantity |
|---|---|
| Arduino Uno | 1 |
| Ultrasonic Sensors (HC-SR04) | 3 |
| L293D Motor Driver | 1 |
| BO Gear Motors | 2 |
| Robot Chassis and Wheels | 1 Set |

## Working Principle

The robot uses three ultrasonic sensors to monitor its surroundings:

- Front Sensor: Detects walls and obstacles ahead.
- Left Sensor: Measures the distance from the left wall.
- Right Sensor: Measures the distance from the right wall.

Based on the sensor readings, the Arduino executes the programmed navigation logic and controls the motors through the L293D motor driver.

The robot continuously monitors its surroundings and adjusts its movement to navigate through the maze autonomously.

## Software and Programming

- Programming Language: C++
- IDE: Arduino IDE
- Microcontroller: Arduino Uno
- Motor Driver: L293D
- Navigation Technique: Ultrasonic Sensor-Based Wall Following

## Features

- Autonomous maze navigation.
- Three-direction wall detection.
- Real-time obstacle detection.
- Automatic motor control.
- No manual intervention during navigation.

## Project Details

- Project Type: Personal Project
- Development: Independently designed, assembled, programmed, and tested.
- Semester: 3
- Domain: Robotics and Embedded Systems

## Developer

Suprit Nandlaskar

GitHub: https://github.com/supritN

## License

This project is open-source and available for learning and educational purposes.
