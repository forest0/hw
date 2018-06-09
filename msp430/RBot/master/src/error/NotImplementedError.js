var CustomError = require("./CustomError.js");

class NotImplementedError extends CustomError {
    constructor (message) {
        super(message || "method not implemented");
    }
}

module.exports = NotImplementedError;
