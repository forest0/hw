var AirConditioner = require("./AirConditioner.js").AirConditioner;
var AirConditionerMode = require("./AirConditioner.js").AirConditionerMode;
var AirConditionerWindSpeed = require("./AirConditioner.js").AirConditionerWindSpeed;
var Logger = require("../utils/Logger.js");

class GreeAirConditioner extends AirConditioner {

    constructor() {
        super();

        /* NOTE: the last 3 bit in the beginning half part of code
         *       has been ignored since it is always 010,
         *       so we can use 4 * 2 bytes to represent the code
         *       in lower layer hardware
         */
        this.CODE_LENGTH = 35 - 3 + 32;
        this.code = new Array(this.CODE_LENGTH);

        this.code.fill("0");    // fill code with 0
        this.fillPaddings();

        this.setMode(AirConditionerMode.COOL)
            .setIsRunning(true)
            .setWindSpeed(AirConditionerWindSpeed.AUTO)
            .setIsSweeping(false)
            .setIsSleepMode(false)
            .setTemperature(25)
            .setTimer(null)
            .setIsStrongMode(false)
            .setIsLightOn(true)
            .setIsHealthOn(false)
            .setIsDryingMode(false)
            .setIsVentilationMode(false)
            .setIsUpAndDownSweeping(false)
            .setIsLeftAndRightSweeping(false)
            .setIsShowingTemperature(true)
            .setIsEnergySavingMode(false);
    }

    /* fill fixed paddings in the code */
    fillPaddings() {
        /* some paddings are 0, and they have been taken care
         * in constructor with fill method
         */
        this.code[28] = "1";
        this.code[30] = "1";

        this.code[45] = "1";
    }

    /*
     * calculte check sum and set code
     *
     */
    checkSum() {
        var sum = (parseInt(this.mode, 2) - 1) + (this.temperature - 16) + 5;
        if (this.isLeftAndRightSweeping) {
            sum += 1;
        }
        if (this.isVentilationMode) {
            sum += 1;
        }
        if (this.isEnergySavingMode) {
            sum += 1;
        }

        /*
         * 校验码 = [(模式 - 1) + (温度 - 16) + 5 + 左右扫风 + 换气 + 节能] 取二进制后四位，再逆序
         * e.g. 模式 4，30℃，左右扫风，换气关闭，节能关闭，那么校验码为：
         * (4 - 1) + (30 - 16) + 5 + 1 + 0 + 0 = 23 = 16 + 0 + 4 + 2 + 1 = (10111B)
         * 取低四位为 0111，逆序后为 1110
         *
         */
        const checkSumStartIndex = 60;
        const checkSumLength = 4;
        sum &= 0xf;
        var mask = 1;
        for (var i = 0; i < checkSumLength; ++i) {
            if (mask & sum) {
                this.code[checkSumStartIndex+i] = "1";
            } else {
                this.code[checkSumStartIndex+i] = "0";
            }
            mask <<= 1;
        }

    }

    compile(isHex = true) {
        // calculate checkSum and update corresponding code
        this.checkSum();

        /*
         * I do not use the utility like parseInt then toString
         * because the heading padding zeros are needed.
         */

        /*
         * NOTE that here this.CODE_LENGTH % 4 === 0,
         * so I take the short way, which may cause bug
         * if this.CODE_LENGTH % 4 != 0
         */
        const hexStringLength = this.CODE_LENGTH / 4;
        const codeString = this.code.join("");
        var hexBuffer = new Array(hexStringLength);
        var digit;

        Logger.debug(JSON.stringify({"raw code": this.code}));
        Logger.debug(JSON.stringify({"joined code": this.code.join("")}));

        for (var i = 0; i < hexStringLength; ++i) {
            digit = parseInt(codeString.slice(4*i, 4*(i+1)), 2);
            Logger.debug(JSON.stringify({"iteration": i, "digit": digit}));
            if (digit < 10) {
                hexBuffer[i] = String.fromCharCode(0x30 + digit);
            } else {
                hexBuffer[i] = String.fromCharCode(0x61 + digit - 10);
            }
        }

        if (isHex) {
            return hexBuffer.join("");
        } else {
            return this.code;
        }
    }

    setMode(mode) {
        this.mode = mode;

        const modeStartIndex = 0;
        const modeLength = 3;
        for (var i = 0; i < modeLength; ++i) {
            this.code[i+modeStartIndex] = this.mode[i];
        }

        return this;
    }

    setIsRunning(flag) {
        this.isRunning = flag;

        const isRunningStartIndex = 3;
        if (this.isRunning) {
            this.code[isRunningStartIndex] = "1";
        } else {
            this.code[isRunningStartIndex] = "0";
        }

        return this;
    }

    setWindSpeed(speed) {
        this.windSpeed = speed;

        const windSpeedStartIndex = 4;
        const windSpeedLength = 2;
        for (var i = 0; i < windSpeedLength; ++i) {
            this.code[windSpeedStartIndex+i] = this.windSpeed[i];
        }

        return this;
    }

    setIsSweeping(flag) {
        this.isSweeping = flag;

        const isSweepingStartIndex = 6;
        if (flag) {
            this.code[isSweepingStartIndex] = "1";
        } else {
            this.code[isSweepingStartIndex] = "0";
        }

        return this;
    }

    setIsSleepMode(flag) {
        this.isSleepMode = flag;

        const isSleepModeStartIndex = 7;
        if (flag) {
            this.code[isSleepModeStartIndex] = "1";
        } else {
            this.code[isSleepModeStartIndex] = "0";
        }

        return this;
    }

    setTemperature(temperature) {
        // TODO: <2018-06-06, forest9643,
        //      the max temperature is 30 ?
        if (temperature < 16 || temperature > 30) {
            return;
        }
        this.temperature = temperature;

        /* temperature is encoded by 4 bits as following table
         *
         *       +----+------+
         *       | 16 | 0000 |
         *       +----+------+
         *       | 17 | 1000 |
         *       +----+------+
         *       | .. | .... |
         *       +----+------+
         *       | 30 | 0111 |
         *       +----+------+
         *
         * left column is temperature in centigrade degree
         * right column is the coresponding encoding
         *
         * the rule is that encoding increases one bit at a time in reverse order
         */

        const temperatureStartIndex = 8;
        const temperatureLength = 4;
        var delta = this.temperature - 16;
        var mask = 1;
        for (var i = 0; i < temperatureLength; ++i) {
            if (mask & delta) {
                this.code[temperatureStartIndex+i] = "1";
            } else {
                this.code[temperatureStartIndex+i] = "0";
            }
            mask <<= 1;
        }

        return this;
    }

    setTimer(timer) {
        this.timer = timer;

        // TODO: <2018-06-06, forest9643,
        // timer not implemented
        // just let them to be all zero
        const timerStartIndex = 12;
        const timerLength = 8;
        for (var i = 0; i < timerLength; ++i) {
            this.code[timerStartIndex+i] = "0";
        }

        return this;
    }

    setIsStrongMode(flag) {
        this.isStrongMode = flag;

        const isStrongModeStartIndex = 20;
        if (flag) {
            this.code[isStrongModeStartIndex] = "1";
        } else {
            this.code[isStrongModeStartIndex] = "0";
        }

        return this;
    }

    setIsLightOn(flag) {
        this.isLightOn = flag;

        const isLightOnStartIndex = 21;
        if (flag) {
            this.code[isLightOnStartIndex] = "1";
        } else {
            this.code[isLightOnStartIndex] = "0";
        }

        return this;
    }

    setIsHealthOn(flag) {
        this.isHealthOn = flag;

        const isHealthOnStartIndex = 22;
        if (flag) {
            this.code[isHealthOnStartIndex] = "1";
        } else {
            this.code[isHealthOnStartIndex] = "0";
        }

        return this;
    }

    setIsDryingMode(flag) {
        this.isDryingMode = flag;

        const isDryingModeStartIndex = 23;
        if (flag) {
            this.code[isDryingModeStartIndex] = "1";
        } else {
            this.code[isDryingModeStartIndex] = "0";
        }

        return this;
    }

    setIsVentilationMode(flag) {
        this.isVentilationMode = flag;

        const isVentilationModeStartIndex = 24;
        if (flag) {
            this.code[isVentilationModeStartIndex] = "1";
        } else {
            this.code[isVentilationModeStartIndex] = "0";
        }

        return this;
    }

    setIsUpAndDownSweeping(flag) {
        this.isUpAndDownSweeping = flag;

        const isUpAndDownSweepingStartIndex = 32;
        if (flag) {
            this.code[isUpAndDownSweepingStartIndex] = "1";
        } else {
            this.code[isUpAndDownSweepingStartIndex] = "0";
        }

        return this;
    }

    setIsLeftAndRightSweeping(flag) {
        this.isLeftAndRightSweeping = flag;

        const isLeftAndRightSweepingStartIndex = 36;
        if (flag) {
            this.code[isLeftAndRightSweepingStartIndex] = "1";
        } else {
            this.code[isLeftAndRightSweepingStartIndex] = "0";
        }

        return this;
    }

    setIsShowingTemperature(flag) {
        this.isShowingTemperature = flag;

        // TODO: <2018-06-06, forest9643,
        // 2-bit encoding here?
        const isShowingTemperatureStartIndex = 40;
        const isShowingTemperatureLength = 2;
        for (var i = 0; i < isShowingTemperatureLength; ++i) {
            this.code[isShowingTemperatureStartIndex+i] = "0";
        }

        return this;
    }

    setIsEnergySavingMode(flag) {
        this.isEnergySavingMode = flag;

        const isEnergySavingModeStartIndex = 58;
        if (flag) {
            this.code[isEnergySavingModeStartIndex] = "1";
        } else {
            this.code[isEnergySavingModeStartIndex] = "0";
        }

        return this;
    }
}

module.exports = GreeAirConditioner;
