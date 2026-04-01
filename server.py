from flask import Flask, request, jsonify
from flask_cors import CORS
import joblib
import numpy as np
import mysql.connector

app = Flask(__name__)
CORS(app)

# Load ML model
model = joblib.load("aqi_xgboost_model.pkl")

# MySQL Connection
db = mysql.connector.connect(
    host="localhost",
    user="root",
    password="server1046",
    database="aqi_db"
)

cursor = db.cursor()

latest_data = {}

@app.route('/')
def home():
    return "AQI Server Running"

@app.route('/predict', methods=['POST'])
def predict():
    global latest_data

    data = request.json

    temp = data['temperature']
    mq135 = data['mq135']
    mq7 = data['mq7']
    pm25 = data['pm25']

    features = np.array([[temp, mq135, mq7, pm25]])
    prediction = model.predict(features)

    aqi = int(prediction[0])

    # Save in DB
    cursor.execute(
        "INSERT INTO sensor_data (temperature, mq135, mq7, pm25, aqi) VALUES (%s,%s,%s,%s,%s)",
        (temp, mq135, mq7, pm25, aqi)
    )
    db.commit()

    latest_data = {
        "temperature": temp,
        "mq135": mq135,
        "mq7": mq7,
        "pm25": pm25,
        "aqi": aqi
    }

    return jsonify({"AQI": aqi})


@app.route('/data')
def get_data():
    return jsonify(latest_data)


app.run(host="0.0.0.0", port=5000)