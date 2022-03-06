from pymongo import MongoClient
from fastapi.testclient import TestClient
from ..server.db.mock_data import save_mock_data
from ..server.main import app

server_client = TestClient(app)


#
# Database test for mock data
#
def test_getmockdata():
    save_mock_data({"msg": "Mock Data test"})
    res = server_client.get("/test")
    assert res.status_code == 200
    res_obj = res.json()
    assert res_obj["msg"] == "Mock Data test"
