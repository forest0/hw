// global variables used in multiple modules

var Configurations = require("./config");
var SerialPort = require("serialport");

// serialPort is used in UserCommunicator and DeviceCommunicator
const serialPort = new SerialPort(Configurations.serial);

module.exports = {serialPort};
