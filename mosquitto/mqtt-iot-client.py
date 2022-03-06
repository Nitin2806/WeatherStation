import paho.mqtt.client as mqtt
import uuid
import time
import json

BROKER = "127.0.0.1"
PORT = 1883
# uuid1 generates uuid based on hostID and time
client_id = "iot-client-" + str(uuid.uuid1())
sample_data = {
    "temp": 55,
    "loc": {
        "lat": 100,
        "lon": 100
    },
    "humidity": 55,
    "precipitation": False
}


# callbacks
def on_connect(client, userdata, flags, rc, properties=None):
    if rc != 0:
        print("Failed to Connect", rc)
        # exit program
        return


def on_disconnect(client, userdata, flags, rc=0):
    client.loop_stop()
    print("Disconnected " + flags + "result code :" + str(rc))


def on_log(client, userdata, level, buf):
    print("Log :", buf)


# Create client
client = mqtt.Client(client_id, protocol=5)

# Assign callback to client
client.on_connect = on_connect
client.on_disconnect = on_disconnect
client.on_log = on_log
# connect
client.connect(BROKER)

# Loop forever
# callback are activated once the loop start
client.loop_start()

while True:
    client.publish("weather/" + client_id, json.dumps(sample_data))
    # pubish every minute
    time.sleep(10)

client.disconnect()
client.loop_stop()