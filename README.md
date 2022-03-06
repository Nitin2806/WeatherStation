#Weather Station


## Tech Stack

IOT [Aurduino](https://www.arduino.cc/)

MQTT Server [Mosquitto](https://mosquitto.org/)

MQTT Client [paho-mqtt/py](https://www.eclipse.org/paho/index.php?page=clients/python/docs/index.php)

Database (noSQL) [MongoDB](https://docs.mongodb.com/)

Mongo-Client [pymongo/py](https://pymongo.readthedocs.io/en/stable/)

Backend (RESTapi) [FastAPI/py](https://fastapi.tiangolo.com/)

Frontend (webapp) [reactjs/js](https://reactjs.org/)

Machine Learning

## Connection

IOT (mqtt-client) <-MQTT-> (MOSQUITTO mqtt-server) <-MQTT-> (paho-mqtt mqtt-client)--(mongodb database)--(backend/api) <-HTTP-> client (using client-script)

## Setup

### MOSQUITTO (MQTT-server/broker)

```sh
    # install mosquitto
    apt install mosquitto
    # start mosquitto broker/server
    mosquitto -c CONF_FILE  -d

    # in case of `Error: Address already in use`
    ps -ef | grep mosquitto     # get process id PID
    sudo kill PID               # kill process
    mosquitto -c CONF_FILE  -d  # start broker/server

    # In case running locally on wifi-network
    hostname -I             # get private IP to be used as broker IP
```

### MONGODB

For Linux
[Install Guide](https://docs.mongodb.com/manual/tutorial/install-mongodb-on-ubuntu/)

For Windows
[Install Guide](https://docs.mongodb.com/manual/tutorial/install-mongodb-on-windows/)

### ENVIRONMENT

```sh
    cd backend/
    python3 -m venv venv                # create virtual env `venv`
    source venv/bin/activate            # activate venv
    pip install -r requirements.txt     # install dependencies
```

## Starting HTTP server

```sh
    uvicorn backend.server.main:app

    # development server (hot-reload)
    uvicorn backend.server.main:app --reload
```

## Writing Test

This repository uses `pytest` and requires test to follow [Python test discovery Conventions](https://docs.pytest.org/en/stable/goodpractices.html#test-discovery)


## MERN
### Mongoose library
Connection between Mongodb and Mongoose



