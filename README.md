## AI-Based Motion Detection with Telegram Notification

This project is a smart security system that uses a **Python-based AI motion detector** with a **laptop webcam** to monitor activity. When motion is detected, it captures an image and notifies the user via **Telegram**, using an ESP8266 microcontroller to send the message and photo.

-

 Features

- 📷 Real-time motion detection using laptop webcam
- 🤖 AI-based logic using Python and OpenCV
- 🌐 Local Flask server to serve captured images
- 📩 ESP8266 connects to Wi-Fi and triggers Telegram alert
- 🛡️ Useful for home security, surveillance, or remote monitoring



 Tech Stack

   Component                   Technology 
 AI & Motion Detection      Python + OpenCV
 Backend Server             Flask (Python) 
 Microcontroller            ESP8266 (NodeMCU) 
 Messaging                  Telegram Bot API 
 IDEs                      VS Code, Arduino IDE 
 Hosting                   Local Network (LAN) 


🗂️ Project Structure

bash
AI-Motion-Detection/
│
├── motion_detector.py         # Detects motion and captures photo
├── flask_server.py            # Serves the captured photo over HTTP
├── esp8266_motion_trigger.ino # Sends Telegram message with photo
├── requirements.txt           # Python dependencies
└── README.md                  # Project overview (this file)
