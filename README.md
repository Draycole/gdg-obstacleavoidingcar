# Autonomous Obstacle-Avoiding Robot (Prototype Build)

This is a simple autonomous robot built as a **minimum working model** for the GDG Robotics & Embedded Systems Track. Using an ultrasonic sensor, it continuously scans its surroundings and chooses the safest direction to move.  
Despite limited components at the time, the team assembled a fully functional prototype during a study jam session.

---

## 🚗 Overview
The robot:
- Moves forward for a short interval  


This loop allows the robot to navigate around obstacles autonomously. 

---

## 🧩 Components Used
- Arduino Uno  
- L298N Motor Driver  
- 2 × DC Motors + Wheels (2WD chassis)  
- Ultrasonic Sensor (HC-SR04)  
- 5V 3A Power Supply   
- Jumper wires  
- Basic frame

---

## 📸 Media
<!-- _Add photos and GIFs in a `/media` folder and remember to link them here bro._ -->
![Project Demo Pic](./media/demo%20video.gif)


---

## 🔌 Circuit Diagram
![Project Circuit Schematic](./media/schematic%20diagram.png)

---

## 🧠 How It Works
1. Robot moves forward for ~2 seconds  
2. Stops and takes three distance readings  
3. Compares them to find the safest direction  
4. Executes a left turn, right turn, reverse, or forward continuation  
5. Repeats indefinitely  

---

## 💻 Code
The full Arduino code is available in `/code/sourcecode/sourcecode.ino`.

---

## 🚀 Setup & Usage
1. Assemble the chassis and connect motors to L298N  
2. Set the ultrasonic sensor on the servo, mounted on the chassis  
3. Connect the ultrasonic sensor to Arduino
4. Wire L298N to Arduino digital pins  
5. Upload the code  
6. Power the robot using the battery pack  
7. Place it on a flat surface and let it run

---

## 📚 Future Improvements
- Add Bluetooth override mode  
- Add IR edge detection sensors  
- Replace prototype chassis with a full kit  
- Implement PID-based turning for smoother maneuvers  

---

## 📄 License
This project is licensed under the **MIT License**.



