# 🔐 Secure Pro – Advanced Multi-Level Security System

A smart multi-factor authentication system that combines **Face Recognition**, **Fingerprint Authentication**, and **PIN Verification** to provide enhanced access control. The project integrates **Python OpenCV** for face recognition with an **Arduino Uno** for hardware control.

---

## 📖 Project Overview

Traditional security systems rely on a single authentication method, making them vulnerable to unauthorized access. **Secure Pro** introduces a **three-level authentication system** to improve security by combining:

- 👤 Face Recognition (Python + OpenCV)
- 👆 Fingerprint Authentication (R307S)
- 🔢 PIN Verification (4×4 Keypad)

Only after all three authentication stages are successfully completed does the system unlock the door using an SG90 servo motor.

---

## ✨ Features

- ✅ Real-time face recognition using OpenCV (LBPH Algorithm)
- ✅ Unknown face detection
- ✅ Fingerprint authentication using R307S sensor
- ✅ 4×4 keypad PIN verification
- ✅ SG90 servo motor-based door locking mechanism
- ✅ 16×2 I2C LCD status display
- ✅ Serial communication between Python and Arduino
- ✅ Multi-factor authentication (3-Level Security)
- ✅ Automatic system reset after successful or failed authentication

---

# 🛠 Hardware Used

| Component | Quantity |
|------------|----------|
| Arduino Uno | 1 |
| R307S Fingerprint Sensor | 1 |
| SG90 Servo Motor | 1 |
| 16×2 I2C LCD Display | 1 |
| 4×4 Matrix Keypad | 1 |
| USB Webcam / ESP32-CAM | 1 |
| Breadboard & Jumper Wires | As Required |

---

# 💻 Software Requirements

- Python 3.11+
- Arduino IDE
- Visual Studio Code

### Python Libraries

```bash
pip install opencv-contrib-python
pip install pyserial
pip install numpy
```

---

# 📚 Arduino Libraries

Install the following libraries from the Arduino Library Manager:

- Adafruit Fingerprint Sensor Library
- LiquidCrystal_I2C
- Keypad
- Servo
- SoftwareSerial

---

# 🧠 Technologies Used

- Python
- OpenCV
- Arduino C++
- Serial Communication
- Machine Learning (LBPH Face Recognizer)

---

# 🔌 Serial Communication

Python sends commands to Arduino through the serial port.

| Command | Meaning |
|----------|----------|
| F | Face Verified |


Arduino controls:

- Fingerprint Verification
- Keypad Verification
- Servo Motor
- LCD Display

---

# 🔐 Security Features

- Three-Level Authentication
- Unknown Face Detection
- Unknown Fingerprint Detection
- Incorrect PIN Detection
- Automatic Door Relock
- Authentication Timeout
- Access Denied on Any Failure

---

# 📸 Face Recognition

The system uses:

- Haar Cascade Face Detection
- LBPH Face Recognition

Recognition is performed in real time using a webcam.

---

# 👆 Fingerprint Authentication

The R307S sensor:

- Captures fingerprint
- Matches stored templates
- Returns fingerprint ID
- Grants access only to enrolled users

---

# 🔢 PIN Verification

After successful fingerprint verification:

- User enters a 4-digit PIN
- Password is masked on LCD
- Wrong PIN resets the authentication process

---

# 🚪 Door Locking Mechanism

An SG90 servo motor acts as the door lock.

- 0° → Locked
- 50° → Unlocked

After a predefined delay, the servo automatically returns to the locked position.

---

# 🚀 Future Enhancements

- Mobile App Integration
- IoT Cloud Monitoring
- Email/SMS Alerts
- Intruder Image Capture
- Face Anti-Spoofing
- RFID Backup Authentication
- Attendance Logging
- Remote Door Access

---

# 📈 Applications

- Smart Homes
- Offices
- Laboratories
- Server Rooms
- Banks
- Hospitals
- Educational Institutions
- Government Offices

---

# 👩‍💻 Developed By

**Vaishnavi Shaw**

For 

Final Year B.Tech (Electronics & Communication Engineering)

Major Project

---

# 📜 License

This project is developed for educational and academic purposes.

Feel free to use and modify it with proper attribution.

---

## ⭐ If you found this project useful, consider giving it a Star!
