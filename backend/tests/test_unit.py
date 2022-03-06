from pymongo import MongoClient
from fastapi.testclient import TestClient

from ..server.main import app

server_client = TestClient(app)


def func():
    return True


def test_unit():
    assert func()


def test_db_init():
    client = MongoClient()
    assert client
    db = client["test"]
    assert db
    test_collection = db["test_collection"]
    assert test_collection
    test_collection.insert_one({"valid": True})
    doc = test_collection.find_one({"valid": {"$exists": True}})
    assert doc["_id"]
    assert doc["valid"]
    print(doc)


def test_server_init():
    response = server_client.get("/")
    assert response.status_code == 200
    assert response.json() == {"msg": "Hello World"}
