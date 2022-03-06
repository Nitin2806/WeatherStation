const express = require('express');
const MongoClient = require('mongodb').MongoClient
const bodyParser = require('body-parser')
var ObjectID = require('mongodb').ObjectID;
const app = express();
const router = require('express').Router();

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));

MongoClient.connect('mongodb://127.0.0.1:27017/', (err, db) => {
    if (err) return console.log(err)

    app.listen(3000, () => {
        console.log('app working on 3000')
    });

    let dbase = db.db("Forecast");

    app.get('/data', (req, res, next) => {
        dbase.collection('Forecast_collection').find({}).toArray((err, results) => {
            res.send(results);

        });
    });

    // app.get('/data/:id/', (req, res, next) => {
    //     if (err) {
    //         throw err;
    //     }

    //     let id = ObjectID(req.params.id);
    //     dbase.collection('Forecast_collection').find(id).toArray((err, result) => {
    //         if (err) {
    //             throw err;
    //         }

    //         res.send(result);
    //     });
});