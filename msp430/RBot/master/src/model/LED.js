// LED Model
class LED {
    constructor() {
        this.redOn = false;
        this.greenOn = false;
    }

    setRed(flag) {
        this.redOn = flag;
    }

    setGreen(flag) {
        this.greenOn = flag;
    }

    compile() {
        /* command string for serial
         * consists 2 digits,
         * the first represents red,
         * the second represents green,
         * the value(0, 1) represents status
         */
        var redStr = this.redOn?"1":"0";
        var greenStr = this.greenOn?"1":"0";
        return redStr + greenStr;
    }
}

module.exports = LED;
