const Logger = require("../utils/Logger.js");

const CommandTypes = {
    "LED" : "0",
    "TEMPERATURE_SENSOR" : "1",
    "AIR_CONDITIONER" : "2",
    "HEART_BEAT" : "3",
    "INVALID" : "4"
};

//var serialPort = new SerialPort(Configurations.serial);
var serialPort = require("../../global").serialPort;
var portOpened = false;

function openPort() {
    // open serial port
    serialPort.on("open", function(error) {
        if (error) {
            portOpened=false;
            Logger.error(error);
        } else {
            Logger.info("Port checked: port is open");
            portOpened=true;
        }

    });
}



function sendCommand(commandType, arg = "") {
    if (portOpened) {
        serialPort.write(commandType + arg, function(error) {
            if (error) {
                Logger.error(error);
            }
        });
    } else {
        Logger.info("SerialPort Unreachable");
    }
}


module.exports = {CommandTypes, openPort, sendCommand};
