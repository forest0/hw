var UserCommunicator = require("./src/communicator/UserCommunicator");

var openPort = require("./src/communicator/DeviceCommunicator").openPort;
openPort();

var userCommunicator = new UserCommunicator();

userCommunicator.registerMessageReceiveEvent();
userCommunicator.registerCommandReceiveEvent();