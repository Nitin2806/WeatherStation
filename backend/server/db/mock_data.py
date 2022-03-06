from pymongo import MongoClient
from datetime import datetime, timedelta

client = MongoClient()
db = client["test"]
test_collection = db.get_collection("test_collection")


def save_mock_data(data: dict) -> list:
    """Saves data to the database
    Data is expected to be JSON/dict 
    
    Returns: list of _id of inserted docs 
    """
    assert isinstance(data, dict)
    data["timestamp"] = datetime.utcnow()
    res = test_collection.insert_one(data)
    return res.inserted_id


def get_mock_data() -> dict:
    after = datetime.utcnow() - timedelta(minutes=1)
    doc = test_collection.find_one({"timestamp": {"$gt": after}}, {"_id": 0})
    #doc["_id"] = str(doc["_id"])
    return doc
