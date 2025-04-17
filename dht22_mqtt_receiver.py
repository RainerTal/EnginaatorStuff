import paho.mqtt.client as mqtt
import time
import json
import datetime

# MQTT broker address (this is the Raspberry Pi itself)
broker_address = "localhost"

# Dictionary to store the latest sensor readings
sensor_data = {
    "humidity": None,
    "temperatureC": None,
    "temperatureF": None,
    "heatIndexC": None,
    "heatIndexF": None,
    "timestamp": None
}

# Callback when connecting to the MQTT broker
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    # Subscribe to all ESP32 topics
    client.subscribe("esp32/#")

# Callback when a message is received
def on_message(client, userdata, msg):
    global sensor_data
    topic = msg.topic
    value = float(msg.payload.decode())
    
    print(f"Received: {topic} = {value}")
    
    # Update the appropriate sensor data based on topic
    if topic == "esp32/humidity":
        sensor_data["humidity"] = value
    elif topic == "esp32/temperatureC":
        sensor_data["temperatureC"] = value
    elif topic == "esp32/temperatureF":
        sensor_data["temperatureF"] = value
    elif topic == "esp32/heatIndexC":
        sensor_data["heatIndexC"] = value
    elif topic == "esp32/heatIndexF":
        sensor_data["heatIndexF"] = value
    
    # Update timestamp whenever any data is received
    sensor_data["timestamp"] = datetime.datetime.now().isoformat()
    
    # Save data to file
    save_sensor_data()
    
    # Optionally request a new reading
    # client.publish("esp32/commands", "getReading")

def save_sensor_data():
    """Save the current sensor data to a JSON file"""
    try:
        with open('sensor_data.json', 'w') as f:
            json.dump(sensor_data, f, indent=4)
    except Exception as e:
        print(f"Error saving data: {e}")

def request_reading():
    """Request a new sensor reading from the ESP32"""
    client.publish("esp32/commands", "getReading")
    print("Requested new sensor reading")

# Create MQTT client
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

# Connect to broker
client.connect(broker_address, 1883, 60)

# Start the loop
client.loop_start()

print("MQTT Client is running. Press Ctrl+C to exit.")
print("Current data will be saved to sensor_data.json")

try:
    # Optional: Periodically request new readings
    while True:
        time.sleep(60)  # Request a new reading every minute
        request_reading()
except KeyboardInterrupt:
    print("\nExiting...")
    client.loop_stop()
