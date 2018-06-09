const winston = require("winston");
const myFormat = winston.format.combine(
    winston.format.timestamp(),
    // winston.format.prettyPrint(),
    winston.format.printf(info => {
        return `${info.timestamp} [${info.level}]: ${info.message}`;
    })
);

const Logger = winston.createLogger({
    // TODO: <2018-06-05, forest9643, read option from config> //
    level: "info",
    format: myFormat
});
// If we're not in production then log to the `console` with the format:
// `${info.level}: ${info.message} JSON.stringify({ ...rest }) `
//
if (process.env.NODE_ENV !== "production") {
    Logger.add(new winston.transports.Console({
        format: myFormat
    }));
}

module.exports = Logger;
