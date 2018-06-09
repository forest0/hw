const Logger = require("../utils/Logger.js");

// Air Conditioner
var AirConditionerMode = require("../model/AirConditioner.js").AirConditionerMode;
var AirConditionerWindSpeed = require("../model/AirConditioner.js").AirConditionerWindSpeed;
var GreeAirConditioner = require("../model/GreeAirConditioner.js");

// Device Communicator
var CommandTypes = require("../communicator/DeviceCommunicator").CommandTypes;
var sendCommand = require("../communicator/DeviceCommunicator").sendCommand;

// 空调命令枚举
var AirConditionerCommands = {
    "TURN_ON": 0,
    "TURN_OFF": 1,
    "SET_MODE": 2,
    "SET_WIND_SPEED": 3,
    "SET_TEMPERATURE": 4,
    "SET_STRONG_MODE": 5,
    // TODO: <2018-06-05, forest9643, support more command> //
};
Object.freeze(AirConditionerCommands);

const UserAirConditionerMode = {
    "auto"     : "000",          // 自动
    "cool"     : "100",          // 制冷
    "humidify" : "010",          // 加湿
    "wind"     : "110",          // 送风
    "warm"     : "001",          // 制热
};

var UserCommands = {
    "HELP" : "help",
    "SHOW_STATUS" : "status",
    "MODE" : "mode",
    "RUNNING_STATE" : "running status",
    "SHOW_TEMPERATURE" : "temperature",


    "TURN_ON" : "turn on",
    "TURN_OFF" : "turn off",
    "SET_TEMPERATURE" : "set temperature",
    "SET_STRONG_MODE" : "set strongmode",
    "SET_MODE" : "set mode",
};
Object.freeze(UserCommands);

class AirConditionerController {
    constructor() {
        this.greeAirConditioner = new GreeAirConditioner();
        // TODO: <2018-06-05, forest9643, open serial according to config> //
        //this.serialPort = new SerialPort(Configurations.serial);
    }

    calculateCheckSum() {

    }

    // receive command from UserCommunicator
    receiveCommand(command) {
        var arg = "";
        var commandList = command.split(" ");
        if (commandList.length == 3) {
            command = commandList.slice(0, commandList.length-1).join(" ");
            arg = commandList[2];
        }

        var replyMessage = "";
        switch (command) {
            // read status
            case UserCommands.HELP: {
                replyMessage = this.getHelpMessage();
                break;
            }
            case UserCommands.SHOW_STATUS: {
                replyMessage = this.getReadableStatus();
                break;
            }
            case UserCommands.MODE: {
                replyMessage = "Current mode is " +
                    this.getKeyByValue(AirConditionerMode, this.greeAirConditioner.mode);
                break;
            }
            case UserCommands.RUNNING_STATE: {
                replyMessage = "The air conditioner is " +
                    (this.greeAirConditioner.isRunning? "On": "Off");
                break;
            }
            case UserCommands.TEMPERATURE: {
                replyMessage = "Current temperature is: " + this.greeAirConditioner.temperature + "°C";
                break;
            }

            // modify
            case UserCommands.TURN_ON: {
                this.turnOn();
                break;
            }
            case UserCommands.TURN_OFF: {
                this.turnOff();
                break;
            }
            case UserCommands.SET_TEMPERATURE: {
                this.setTemperature(arg);
                break;
            }
            case UserCommands.SET_STRONG_MODE: {
                this.setIsStrongMode(true);
                break;
            }
            case UserCommands.SET_MODE: {
                this.setMode(arg);
                break;
            }
            default: {
                replyMessage = "No such command, type \"help\" for usages 😊";
                break;
            }
        }
        return replyMessage;
    }


    getKeyByValue(object, value) {
        return Object.keys(object).find(key => object[key] === value);
    }

    helpMessage() {
        var helpMsg = "Gree Air Conditioner Control Module\n" +
                      "Usages:\n" +
                      "- status: Display the status of air conditioner\n" +
                      "- mode: Display the mode" +
                      "- running status: Display running status (On or Off)" +
                      "- temperature: Display current temperature" +
                      "- turn on: Turn on the air conditioner\n" +
                      "- turn off: Turn off the air conditioner\n" +
                      "- set temperature [NUM]: set temperature to given number\n" +
                      "- set mode [auto/cool/humidify/wind/warm]: set the mode of Air Conditioner\n"
                      ;
        return helpMsg;
    }

    // display parameter to user
    getReadableStatus() {
        var status = "Air Conditioner Status:\n" +
                        "Mode: " + this.getKeyByValue(AirConditionerMode, this.greeAirConditioner.mode) + "\n" +
                        "Running State: " + (this.greeAirConditioner.isRunning? "Running": "Stopped") + "\n" +
                        "Wind Speed: " + this.getKeyByValue(AirConditionerWindSpeed, this.greeAirConditioner.windSpeed) + "\n" +
                        "IsSweeping: " + this.greeAirConditioner.isSweeping + "\n" +
                        "Temperature: " + this.greeAirConditioner.temperature + "(Celsius)\n" +
                        "Timer: " + this.greeAirConditioner.timer + "\n" +
                        "IsStrongMode: " + this.greeAirConditioner.isStrongMode + "\n" +
                        "IsLightOn: " + this.greeAirConditioner.isLightOn + "\n" +
                        "isHealthOn: " + this.greeAirConditioner.isHealthOn + "\n" +
                        "IsDryingMode: " + this.greeAirConditioner.isDryingMode + "\n" +
                        "IsVentilationMode: " + this.greeAirConditioner.isVentilationMode + "\n" +
                        "IsUpAndDownSweeping: " + this.greeAirConditioner.isUpAndDownSweeping + "\n" +
                        "IsLeftAndRightSweeping: " + this.greeAirConditioner.isLeftAndRightSweeping + "\n" +
                        "IsShowingTemperature: " + this.greeAirConditioner.isShowingTemperature + "\n" +
                        "IsEnergySavingMode: " + this.greeAirConditioner.isEnergySavingMode + "\n";
        return status;
    }

    turnOn() {
        this.greeAirConditioner.setIsRunning(true);
        var encoding = this.greeAirConditioner.compile();
        sendCommand(CommandTypes.AIR_CONDITIONER, encoding);
    }

    turnOff() {
        this.greeAirConditioner.setIsRunning(false);
        var encoding = this.greeAirConditioner.compile();
        Logger.info(encoding);
        sendCommand(CommandTypes.AIR_CONDITIONER, encoding);
    }

    setTemperature(temperature) {
        this.greeAirConditioner.setTemperature(temperature);
        var encoding = this.greeAirConditioner.compile();
        sendCommand(CommandTypes.AIR_CONDITIONER, encoding);
    }

    setIsStrongMode(flag) {
        this.greeAirConditioner.setIsStrongMode(flag);
        var encoding = this.greeAirConditioner.compile();
        sendCommand(CommandTypes.AIR_CONDITIONER, encoding);
    }

    setMode(flag) {
        this.greeAirConditioner.setMode(UserAirConditionerMode[flag]);
        var encoding = this.greeAirConditioner.compile();
        sendCommand(CommandTypes.AIR_CONDITIONER, encoding);
    }
}

module.exports = AirConditionerController;
