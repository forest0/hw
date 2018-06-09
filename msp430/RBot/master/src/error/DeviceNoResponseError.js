var CustomError = require("./CustomError.js");

class DeviceNoResponseError extends CustomError {
    constructor (message) {
        super(message || "device no response");
    }
}

module.exports = DeviceNoResponseError;
