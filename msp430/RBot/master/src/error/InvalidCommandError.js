var CustomError = require("./CustomError.js");

class InvalidCommandError extends CustomError {
    constructor (message) {
        super(message || "invalid command");
    }
}

module.exports = InvalidCommandError;
