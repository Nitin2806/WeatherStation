import React, { useState, useEffect } from "react";
import "./App.css";
import axios from "axios";

const bUrl = "http://localhost:3000/data";

function App() {
    const [userData, setUserData] = useState({});

    useEffect(() => {
        getGitHubUserWithFetch();
    }, []);

    const AAxios = async() => {
        const response = await axios.get(Url);
        setUserData(response.data);
    };

    return ( <
        div className = "App" >
        <
        header className = "App-header" >
        <
        div className = "user-container" >
        <
        h5 className = "info-item" > { data.Temp } < /h5> <
        h5 className = "info-item" > { data.Humidity } < /h5> < /
        div > <
        /div>
    );
}