import React from "react";

export default class Weather extends React.Component {
        state = {
            loading: true,

        };

        async componentDidMount() {
            const url = "http://localhost:3000/data";
            const response = await fetch(url);
            const data = await response.json();
            console.log(data);

        }

        render() {
            return ( <
                div > {
                    this.state.loading ? < div > loading < /div> : <div>got it { data.Temp } < /div > } < /
                    div >
                );
            }
        }