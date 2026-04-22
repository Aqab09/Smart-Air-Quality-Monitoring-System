from flask import Flask, request, jsonify
from flask_cors import CORS
import joblib
import numpy as np
import mysql.connector

app = Flask(__name__)
CORS(app)   # 🔥 Important for browser requests

# Load ML model
model = joblib.load("aqi_xgboost_model.pkl")

# Store latest sensor data
latest_data = {}

db = mysql.connector.connect(
    host="localhost",
    user="root",
    password="pass", # your password of the database 
    database="Your_Databse_name" #Add your databse name here 
)

cursor = db.cursor()



# -------- AQI CATEGORY --------
def get_aqi_category(aqi):
    if aqi <= 50:
        return "Good 😊"
    elif aqi <= 100:
        return "Moderate 😐"
    elif aqi <= 200:
        return "Unhealthy 😷"
    elif aqi <= 300:
        return "Very Unhealthy ☠️"
    else:
        return "Hazardous 🚨"

# -------- RECEIVE DATA FROM ESP32 --------
@app.route('/data', methods=['POST'])
def receive_data():
    global latest_data

    try:
        data = request.get_json()
        latest_data = data   # ✅ still storing in RAM

        print("\n📥 Data received from ESP32:")
        print(data)

        # Extract values
        temperature = float(data.get('temperature', 0))
        co = float(data.get('co', 0))
        nh3 = float(data.get('nh3', 0))
        benzene = float(data.get('benzene', 0))
        pm25 = float(data.get('pm25', 0))

        # (optional) predict AQI using your model
        features = np.array([[pm25, co, nh3, benzene]])
        aqi = float(model.predict(features)[0])

        query = """
        INSERT INTO sensor_data (temperature, co, nh3, benzene, pm25, aqi)
        VALUES (%s, %s, %s, %s, %s, %s)
        """
        values = (temperature, co, nh3, benzene, pm25, aqi)

        cursor.execute(query, values)
        db.commit()

        print("✅ Stored in MySQL (background only)")

        return jsonify({"status": "received"})

    except Exception as e:
        return jsonify({"error": str(e)}), 400


# -------- SEND DATA TO DASHBOARD --------
@app.route('/data', methods=['GET'])
def send_data():
    return jsonify(latest_data)


# -------- AQI PREDICTION --------
@app.route('/predict', methods=['POST'])
def predict():
    try:
        data = request.get_json()

        pm25 = float(data['pm25'])
        co = float(data['co'])
        nh3 = float(data['nh3'])
        benzene = float(data['benzene'])

        features = np.array([[pm25, co, nh3, benzene]])

        prediction = model.predict(features)[0]
        prediction = round(float(prediction), 2)

        category = get_aqi_category(prediction)

        response = {
            "AQI": prediction,
            "Category": category
        }

        print("📤 AQI Prediction:", response)

        return jsonify(response)

    except Exception as e:
        print("❌ Error:", str(e))
        return jsonify({"error": str(e)}), 400


# -------- RUN SERVER --------
if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000, debug=True)
