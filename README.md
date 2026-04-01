# Smart-Air-Quality-Monitoring-System
This project is a Smart Air Quality Monitoring System that uses IoT sensors, Machine Learning, and a real-time dashboard to monitor and analyze air quality. The system collects environmental data using an ESP32 microcontroller and predicts the Air Quality Index (AQI) using a trained ML model. 

# 🌍 Smart Air Quality Monitoring System (IoT + ML + Dashboard)

## 📌 Overview

This project is a **Smart Air Quality Monitoring System** that combines **IoT sensors, Machine Learning, and a real-time dashboard** to monitor environmental conditions and predict the **Air Quality Index (AQI)**.

An ESP32 microcontroller collects sensor data and sends it to a Flask backend, where an ML model predicts AQI. The results are displayed on a **responsive, app-like dashboard** accessible from both desktop and mobile devices.

---

## 🚀 Features

* 📡 **Real-time Data Collection**

  * 🌡 Temperature (LM35)
  * 🌫 Air Quality (MQ135)
  * ☠ CO Gas Level (MQ7)
  * 🌬 PM2.5 Dust Sensor

* 🤖 **Machine Learning Prediction**

  * AQI prediction using **XGBoost model**

* 📊 **Interactive Dashboard**

  * Live graphs (AQI, Temperature, MQ135, MQ7, PM2.5)
  * App-like UI with navigation
  * Mobile responsive design

* 🧠 **Health Risk Analysis**

  * AQI categories (Good, Moderate, Unhealthy, etc.)
  * Real-time health recommendations

* ⚠️ **Smart Alert System**

  * Visual warnings for dangerous AQI levels
  * Dynamic color indicators

* 📱 **Mobile Access**

  * Dashboard accessible via local network on mobile

---

## 🏗️ System Architecture

ESP32 Sensors → Flask Backend → ML Model → Dashboard UI → User (Mobile/Desktop)

---

## 🛠️ Technologies Used

* **Hardware:** ESP32, MQ135, MQ7, LM35, PM2.5 Sensor
* **Backend:** Python, Flask
* **Machine Learning:** XGBoost, NumPy, Joblib
* **Frontend:** HTML, CSS, JavaScript, Chart.js
* **Database (Optional):** MySQL

---

## ⚙️ How It Works

1. ESP32 collects real-time sensor data
2. Sends data to Flask server via HTTP
3. Flask processes data and predicts AQI using ML model
4. Dashboard fetches data periodically
5. Displays graphs, AQI value, and health warnings

---

## 📊 Dashboard Features

* 📈 Real-time graphs
* 📱 Mobile-friendly app UI
* 🎯 AQI color indicators
* 🧠 Health risk messages
* ⚠️ Warning alerts for high AQI

---

## 📂 Project Structure

```
AQI_Project/
│
├── server.py              # Flask backend
├── index.html            # Dashboard UI
├── aqi_xgboost_model.pkl # ML model
├── sensors_code.ino      # ESP32 code
├── requirements.txt
└── README.md
```

---

## ▶️ How to Run

### 1️⃣ Start Flask Server

```bash
python server.py
```

---

### 2️⃣ Run Dashboard

```bash
python -m http.server 5500
```

Open in browser:

```
http://<your-ip>:5500
```

---

### 3️⃣ Connect ESP32

* Update WiFi credentials
* Update server IP in ESP32 code
* Upload code

---

## 📱 Mobile Access

Make sure both devices are on the same network, then open:

```
http://<your-ip>:5500
```

---

## 🎯 Applications

* 🌆 Smart Cities
* 🏭 Industrial Monitoring
* 🏥 Health Awareness
* 🌍 Environmental Monitoring

---

## 🔮 Future Enhancements

* ☁️ Cloud deployment
* 📱 Native mobile app
* 🔔 SMS/notification alerts
* 🤖 Advanced AI models (LSTM)
* 📊 Data analytics & reports

---

## 👨‍💻 Author

**Aqab**
Engineering Student

---

## ⭐ Conclusion

This project demonstrates the integration of **IoT, Machine Learning, and Web Technologies** to build a real-time air quality monitoring system with practical applications in modern smart environments.

---

## 📸 Screenshots

<img width="1919" height="868" alt="Screenshot 2026-03-26 210249" src="https://github.com/user-attachments/assets/0e9e85d6-f0e0-4190-a42f-8e6a1cdb588f" />
<img width="1919" height="864" alt="Screenshot 2026-03-26 210429" src="https://github.com/user-attachments/assets/0b587d06-59f5-477a-ba36-cae8d6f93e40" />
<img width="1919" height="793" alt="Screenshot 2026-03-26 210452" src="https://github.com/user-attachments/assets/ea7e91ad-1fde-44c9-a5ef-49f32f220d11" />


---
