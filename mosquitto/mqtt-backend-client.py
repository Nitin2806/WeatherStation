import paho.mqtt.client as mqtt
#import uuid
import json
from pymongo import MongoClient
from datetime import datetime

#MongoDB Connection
db_client = MongoClient()
db = db_client["Forecast"]
Forecast_collection = db.get_collection("Forecast_data")

BROKER = "127.0.0.1"
PORT = 1883
client_id = "backend-client"  # + str(uuid.uuid1())


# callbacks
def on_connect(client, userdata, flags, rc, properties=None):
    if rc != 0:
        print("Failed to Connect", rc)
        # exit program
        return
    client.subscribe([("uno/weatherStats", 0)])


def on_disconnect(client, userdata, flags, rc=0):
    client.loop_stop()
    print("Disconnected " + flags + "result code :" + str(rc))


def on_log(client, userdata, level, buf):
    print("Log :", buf)


def on_message(client, userdata, m):
    try:
        
        m = json.loads(m.payload)
        assert isinstance(m, dict)
    except Exception:
        print("Messsage is not in JSON format")
    # m["timestamp"] = datetime.utcnow()

    Forecast_collection.update({"_id": client_id}, {"$push": {
        "data":m
    }},
    upsert=True)


# Create client
client = mqtt.Client(client_id, protocol=5)
# Assign callback to client
client.on_connect = on_connect
client.on_disconnect = on_disconnect
client.on_log = on_log
client.on_message = on_message
# connect
client.connect(BROKER)

# Loop forever
# callback are activated once the loop start
client.loop_start()

while True:
    continue

client.disconnect()
client.loop_stop()