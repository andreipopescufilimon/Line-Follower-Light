# HyperLine Robotics Light Speed

## 🚀 About the Project

**HyperLine Robotics Light Speed** is a high-speed line follower robot developed for competitive robotics.

This robot is based on over **5 years of line follower development experience**, with a focus on speed, precision, low weight, and clean mechanical integration. Unlike many high-speed line followers, this version does **not use EDF downforce or an impeller**. Instead, the design focuses on lightweight engineering, efficient traction, custom electronics, and a compact PCB-based chassis.

The goal of this project is to achieve performance close to heavier EDF-powered robots while keeping the robot significantly lighter, simpler, and more efficient.

<img src="https://github.com/andreipopescufilimon/Line-Follower-Light/blob/52b6ceec76d68ca3d147723de904f4a8149ce9b2/media/infomatrix.png" width="600" />

---

## ⚡ Key Advantages

### No Additional Downforce

Many high-speed line follower robots rely on EDFs or impellers to generate downforce. Light Speed is designed to reach competitive speeds without adding artificial weight or extra power consumption.

This makes the robot lighter, more efficient, and mechanically simpler.

### Ultra-Lightweight Design

The robot weighs around **90 g**, which allows fast acceleration, sharp turns, and better agility. Every part of the robot was designed with weight reduction in mind, from the PCB chassis to the sensor connection system.

### Custom 16-Sensor Array

The robot uses a custom-designed 16-sensor array for precise line detection at high speed. The array is built to work together with our public sensor library, allowing fast calibration and reliable readings in different competition conditions.

### PCB Chassis

The main PCB also acts as the robot chassis. This reduces the need for additional structural parts, improves weight distribution, and keeps the layout compact.

### Carbon Fiber Bars and FPC Cables

The sensor board is connected using lightweight **2 mm carbon fiber bars** and **FPC cables**. This keeps the front sensor system stable while reducing unnecessary wiring and weight.

### Custom Motor Mounts and Wheels

The motor mounts and wheel rims are custom-designed and 3D printed from **ABS**. This provides good strength, low weight, and better precision for high RPM use.

---

## 🔬 Technical Details

## Lightweight Architecture

The robot was designed to be fast without relying on generated downforce. Compared with previous EDF-powered designs, this version focuses on reducing mass and improving mechanical efficiency.

Main design choices:

* Around **90 g total weight**
* Optimized component placement
* PCB chassis used as the main structure
* Lightweight front sensor support
* Silicone wheels for high grip
* Reduced vibration through motor and wheel tuning

---

## 🎯 Custom 16-Sensor Array

The sensor array is one of the most important parts of the robot. It allows the robot to detect the line with high resolution and react quickly during fast movement.

<img src="https://github.com/andreipopescufilimon/Line-Follower-Light/blob/ab0e853114b3bbbcb845dd65a65d51d249b9ff3c/media/sensor.png" width="400" />

Features:

* 16 individual line sensors
* Custom high-speed multiplexer integration
* Fast analog reading
* Adaptive calibration
* Designed for competition tracks
* Compatible with our public sensor library

This gives the robot accurate line position data even during aggressive acceleration, braking, and cornering.

---

## 🧩 Custom PCB Chassis

The main chassis is a custom PCB that integrates the robot electronics into one compact board.

<img src="https://github.com/andreipopescufilimon/Line-Follower-Light/blob/ab0e853114b3bbbcb845dd65a65d51d249b9ff3c/media/pcb.png" width="400" />

It includes:

* Motor control circuitry
* Processing unit
* Sensor connectors
* Power distribution
* Compact SMD component layout
* Mounting points for mechanical parts

Using the PCB as the chassis helps reduce weight, simplifies assembly, and improves reliability.

---

## 🔧 Components and Specifications

| Component                     | Description                                                       |
| ----------------------------- | ----------------------------------------------------------------- |
| Custom PCB Chassis            | Main structure, motor control, processing, and power distribution |
| Custom 16-Sensor Array        | High-precision line detection system                              |
| Custom Silicone Wheels        | Designed for grip, speed, and durability                          |
| Custom Wheel Rims             | Lightweight rims designed for high RPM stability                  |
| Lightweight Carbon Fiber Bars | 2 mm carbon fiber bars used for sensor support                    |
| FPC Cables                    | Lightweight flexible cables used to connect the sensor board      |
| Custom Motor Mounts           | 3D printed using CF PLA for strength and precision                |

---

## 🏆 Performance

HyperLine Robotics Light Speed was built to reach performance levels close to heavier EDF-powered line follower robots, while keeping the design lighter and more efficient.

A previous version, **HyperLine Robotics V3**, competed at the **InfoMatrix 2025 World Final**, where it won by more than **2 seconds**.

This version continues that development direction with a cleaner design, lower weight, improved electronics, and better mechanical integration.

This robot won **Robotics Championship 2026** and **InfoMatrix 2026 World Final** by a margin of almost **3-4seconds**.

<img src="https://github.com/andreipopescufilimon/Line-Follower-Light/blob/52b6ceec76d68ca3d147723de904f4a8149ce9b2/media/robotics-championship.png" width="600" />

---

## 🎥 Media

Demonstration video: [https://www.youtube.com/watch?v=pHxVcCjtnts](https://www.youtube.com/watch?v=pHxVcCjtnts)

---

## PCB Schematic
<img src="https://github.com/andreipopescufilimon/Line-Follower-Light/blob/ab0e853114b3bbbcb845dd65a65d51d249b9ff3c/media/schematic.webp" width="600" />

## PCB Layout
<img src="https://github.com/andreipopescufilimon/Line-Follower-Light/blob/ab0e853114b3bbbcb845dd65a65d51d249b9ff3c/media/layout.webp" width="600" />
