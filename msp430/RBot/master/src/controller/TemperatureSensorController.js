var TemperatureSensor = require("../model/TemperatureSensor");
// Device Communicator
var CommandTypes = require("../communicator/DeviceCommunicator").CommandTypes;
var sendCommand = require("../communicator/DeviceCommunicator").sendCommand;

class TemperatureSensorController {
    constructor() {
        this.temperatureSensor = new TemperatureSensor();
    }

    // receive command from UserCommunicator
    receiveCommand(command) {
        sendCommand(CommandTypes.TEMPERATURE_SENSOR);
    }

    helpMessage() {
        return "LED Control Module\n" + 
               "Usages:\n" + 
               "- temperature: Display current temperature\n";
    }
}

module.exports = TemperatureSensorController;
