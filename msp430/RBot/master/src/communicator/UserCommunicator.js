var Configurations = require("../../config");
const Logger = require("../utils/Logger.js");
var Telegram = require("telegram-bot-api");
// controllers
var AirConditionerController = require("../controller/AirConditionerController");
var LEDController = require("../controller/LEDController");
var TemperatureSensorController = require("../controller/TemperatureSensorController");

var UserDeviceType = {
    "AIR_CONDITIONER" : "ac",
    "LED" : "led",
    "SENSOR_TEMPERATURE" : "temperature",
    "HEART_BEAT" : "htbt",
    "HELPER" : "help",
};

// device type of serial message
var SerialMessageDeviceType = {
    "AIR_CONDITIONER" : "AC",
    "LED" : "LED",
    "SENSOR_TEMPERATURE" : "SE_TP",
    "HEART_BEAT" : "HTBT",
};

// class UserCommunicator
// act as the media between user and controllers
class UserCommunicator {
    constructor() {
        // controllers
        this.airConditionerController = new AirConditionerController();
        this.ledController = new LEDController();
        this.temperatureSensorController = new TemperatureSensorController();

        // Telegram API
        this.telegramApi = new Telegram({
            token: Configurations.telegramBotToken,
            updates: {
                enabled: true,
                get_interval: 1000
            }
        });

        // serial Port
        this.serialPort = require("../../global").serialPort;

        // Telegram chatID
        this.chatId = -1;

        // message from serial
        this.serialMessage = "";
    }

    // receive commands from user and
    // cache the commands from controllers into queue
    registerCommandReceiveEvent() {
        var self = this;
        this.telegramApi.on("message", function(message) {
            self.chatId = message.chat.id;

            Logger.info("User command received from " + self.chatId + ": " + message.text);
            var splitMessages = message.text.split(" ");
            var errorMessage = "";

            if (splitMessages.length <= 0) {
                errorMessage = "Wrong command format";
                Logger.error("Error: " + errorMessage);
                self.replyUser(errorMessage + "🙈");
            } else {
                var deviceName = splitMessages[0];
                var command = splitMessages.slice(1, splitMessages.length).join(" ");

                // different controller for devices
                switch (deviceName) {
                // Air Conditioner
                    case UserDeviceType.AIR_CONDITIONER: {
                        Logger.info("Air conditioner command received: " + command);
                        var replyMessage = self.airConditionerController.receiveCommand(command);
                        if (replyMessage != "") {
                            self.replyUser(replyMessage);
                        }
                        break;
                    }
                    case UserDeviceType.LED: {
                        Logger.info("LED command received: " + command);
                        self.ledController.receiveCommand(command);
                        break;
                    }
                    case UserDeviceType.SENSOR_TEMPERATURE: {
                        Logger.info("Temperature Sensor command received: " + command);
                        self.temperatureSensorController.receiveCommand(command);
                        break;
                    }
                    case UserDeviceType.HELPER: {
                        Logger.info("Help request received");
                        if (command == "") {
                            self.replyUser(self.helpMessage());
                        }
                        else {
                            switch (command) {
                                case UserDeviceType.AIR_CONDITIONER: {
                                    self.replyUser(self.airConditionerController.helpMessage());
                                    break;
                                }
                                case UserDeviceType.LED: {
                                    self.replyUser(self.ledController.helpMessage());
                                    break;
                                }
                                case UserDeviceType.SENSOR_TEMPERATURE: {
                                    self.replyUser(self.temperatureSensorController.helpMessage());
                                    break;
                                }
                                default: {
                                    Logger.error("No such device");
                                }
                            }
                        }

                        break;
                    }
                    default: {
                        errorMessage = "No such device " + "\"" + deviceName + "\"";
                        Logger.error("CommandReceiveError: " + errorMessage);
                        self.replyUser(errorMessage + "🙈");
                        break;
                    }
                }
            }
        });
    }

    // receive message from machine
    registerMessageReceiveEvent() {
        var self = this;
        this.serialPort.on("data", function(data) {
            Logger.info("Message from serial:" + data + ", send to " + self.chatId);
            if (self.chatId) {
                /* message from serial will be sent
                 * into small pieces, so we need to
                 * gather the pieces together into
                 * a complete message string
                 */
                if (data.indexOf("\n") == -1) { // not the final piece
                    self.serialMessage += data;
                }
                else {
                    self.serialMessage += data;
                    var readableMessage = self.decodeSerialMessage(self.serialMessage);
                    Logger.info(readableMessage);
                    // send message to user through Telegram API
                    self.replyUser(readableMessage);
                    // re-init serial message
                    self.serialMessage = "";
                }
            } else {
                Logger.error("Recipient ID not defined");
            }
        });
    }

    // decode serial message to readable message for user
    decodeSerialMessage(serialMessage) {
        /* serial message has following format
         * DeviceType : Message
         */
        var messages = serialMessage.split(":");
        var deviceType = messages[0];
        var message = messages[1];

        var readableMessage = "";

        switch (deviceType) {
            case SerialMessageDeviceType.AIR_CONDITIONER: {
                readableMessage = "Message from serial:\n" +
                    "The command to Air Conditioner has received 😊";
                break;
            }
            case SerialMessageDeviceType.LED: {
                var redOn = message[0]=="0"? false: true;
                var greenOn = message[1]=="0"? false: true;
                readableMessage = "Message from serial:\n" +
                    "Red LED is " + (redOn?"On":"Off") + "\n" +
                    "Green LED is " + (greenOn?"On":"Off") + "\n";
                break;
            }
            case SerialMessageDeviceType.SENSOR_TEMPERATURE: {
                readableMessage = "Message from serial:\n" +
                    "Current temperature is: " + message.split("\n")[0] + "°C";
                break;
            }
            case SerialMessageDeviceType.HEART_BEAT: {
                // TODO
                break;
            }
        }
        return readableMessage;
    }



    // reply information to user
    replyUser(data) {
        if (this.chatId) {
            this.telegramApi.sendMessage({
                chat_id: this.chatId,
                text: data
            }, function(err, message) {
                if (err) {
                    Logger.error("Error: " + err + "" + message);
                }
            });
        }
        else {
            Logger.error("Error: Recipient ID not defined");
        }
    }

    // help message
    helpMessage() {
        return "Help:\n" +
            "This is stupid robot than could control multiple devices, including\n" +
            "1. Gree Air Conditioner\n" +
            "2. LED(Red and Green)\n" +
            "3. Temperature Sensor\n\n" +
            "Commands have following format:\n" +
            "    [DevideType] [Command]\n" +
            "[DevideType]: there are 3 devides:\n" +
            "    - ac: Air Conditioner\n" +
            "    - led: LED\n" +
            "    - temperature: Temperature Sensor\n" +
            "For detailed usages of [Command], you could type:\n" +
            "    help [DeviceTpye]\n";
    }
}

module.exports = UserCommunicator;
