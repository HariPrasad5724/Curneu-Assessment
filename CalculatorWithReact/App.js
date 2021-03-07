import React, { Component } from 'react';
import './App.css';
import ResultComponent from './components/ResultTextComponent';
import ButtonComponent from "./components/ButtonComponent";

class App extends Component {
    constructor(){
        super();

        this.state = {
            result: " "
        }
    }

    onClick = button => {

        if(button === "="){
            this.calculate()
        }

        else if(button === "CLR"){
            this.reset()
        }
        else if(button === "BS"){
            this.backspace()
        }

        else {
            this.setState({
                result: this.state.result + button
            })
        }
    };


    calculate = () => {
        var checkResult = ''
        if(this.state.result.includes('--')){
            checkResult = this.state.result.replace('--','+')
        }

        else {
            checkResult = this.state.result
        }

        try {
            this.setState({
                // eslint-disable-next-line
                result: (eval(checkResult) || "" ) + ""
            })
        } catch (e) {
            this.setState({
                result: "error"
            })

        }
    };

    reset = () => {
        this.setState({
            result: ""
        })
    };

    backspace = () => {
        this.setState({
            result: this.state.result.slice(0, -1)
        })
    };

    render() {
        return (
                <div className="calculator-body">
                    <h1>My Calculator</h1>
                    <ResultComponent result={this.state.result}/>
                    <ButtonComponent onClick={this.onClick}/>
                </div>
        );
    }
}
export default App;
