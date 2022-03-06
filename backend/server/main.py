from fastapi import FastAPI
from .db import mock_data
app = FastAPI()


@app.get("/")
def read_test():
    return {"msg": "Hello World"}


@app.get("/test")
def read_mock_data():
    return mock_data.get_mock_data()
