const Logger = require("../utils/Logger.js");
var LED = require("../model/LED");
// Device Communicator
var CommandTypes = require("../communicator/DeviceCommunicator").CommandTypes;
var sendCommand = require("../communicator/DeviceCommunicator").sendCommand;



var LEDLight = {
    "RED" : "red",
    "GREEN" : "green",
};

var LEDStatus = {
    "ON" : "on",
    "OFF" : "off",
};

class LEDController {
    constructor() {
        this.led = new LED();
    }

    // receive command from UserCommunicator
    receiveCommand(command) {
        /* LED command has 2 words:
         * red/green on/off
         * e.g. red on, red off, green on, green off
         */
        var commandList = command.split(" ");

        if (commandList.length >= 3) {
            return;
        }

        var light = commandList[0];
        var status = commandList[1];

        // check status
        switch (status) {
            case LEDStatus.ON: {
                break;
            }
            case LEDStatus.OFF: {
                break;
            }
            default: {
                Logger.error("No such LED Status");
                return;
            }
        }

        switch (light) {
            case LEDLight.RED: {
                this.led.setRed(status=="on"?true:false);
                break;
            }
            case LEDLight.GREEN: {
                this.led.setGreen(status=="on"?true:false);
                break;
            }
            default: {
                Logger.error("No such LED light type");
                break;
            }
        }

        Logger.info(this.led.redOn+" "+this.led.greenOn);

        var encoding = this.led.compile();

        sendCommand(CommandTypes.LED, encoding);
    }

    helpMessage() {
        return "LED Control Module\n" +
               "Usages:\n" +
               "- [red/green] [on/off]: Control the lights\n";
    }
}

module.exports = LEDController;
