var NotImplementedError = require("../error/NotImplementedError.js");

// 空调运行模式枚举
const AirConditionerMode = {
    "AUTO"     : "000",          // 自动
    "COOL"     : "100",          // 制冷
    "HUMIDIFY" : "010",          // 加湿
    "WIND"     : "110",          // 送风
    "WARM"     : "001",          // 制热
};
Object.freeze(AirConditionerMode);

// 空调风速枚举
const AirConditionerWindSpeed = {
    "AUTO"        : "00",        // 自动
    "LEVEL_ONE"   : "10",        // 一级
    "LEVEL_TWO"   : "01",        // 二级
    "LEVEL_THREE" : "11",        // 三级
};
Object.freeze(AirConditionerWindSpeed);


// AirConditioner Model
// NOTE that this is a virtual base class, should not be used directly
class AirConditioner {

    constructor() {
        this.mode = AirConditionerMode.COOL;            // 运行模式
        this.isRunning = false;                         // 运行/停机
        this.windSpeed = AirConditionerWindSpeed.AUTO;  // 风速
        this.isSweeping = false;                        // 扫风
        this.isSleepMode = false;                       // 睡眠
        this.temperature = 16;                          // 温度
        this.timer = undefined;                         // 定时数据
        this.isStrongMode = false;                      // 超强
        this.isLightOn = true;                          // 灯光
        this.isHealthOn = false;                        // 健康
        this.isDryingMode = false;                      // 干燥
        this.isVentilationMode = false;                 // 换气

        this.isUpAndDownSweeping = false;               // 上下扫风
        this.isLeftAndRightSweeping = false;            // 左右扫风
        this.isShowingTemperature = true;               // 温度显示
        this.isEnergySavingMode = false;                // 节能
    }

    setMode(mode) {
        this.mode = mode;
        return this;
    }

    setIsRunning(flag) {
        this.isRunning = flag;
        return this;
    }

    setWindSpeed(speed) {
        this.windSpeed = speed;
        return this;
    }

    setIsSweeping(flag) {
        this.isSweeping = flag;
        return this;
    }

    setIsSleepMode(flag) {
        this.isSleepMode = flag;
        return this;
    }

    setTemperature(temperature) {
        this.temperature = temperature;
        return this;
    }

    setTimer(timer) {
        this.timer = timer;
        return this;
    }

    setIsStrongMode(flag) {
        this.isStrongMode = flag;
        return this;
    }

    setIsLightOn(flag) {
        this.isLightOn = flag;
        return this;
    }

    setIsHealthOn(flag) {
        this.isHealthOn = flag;
        return this;
    }

    setIsDryingMode(flag) {
        this.isDryingMode = flag;
        return this;
    }

    setIsVentilationMode(flag) {
        this.isVentilationMode = flag;
        return this;
    }

    setIsUpAndDownSweeping(flag) {
        this.isUpAndDownSweeping = flag;
        return this;
    }

    setIsLeftAndRightSweeping(flag) {
        this.isLeftAndRightSweeping = flag;
        return this;
    }

    setIsShowingTemperature(flag) {
        this.isShowingTemperature = flag;
        return this;
    }

    setIsEnergySavingMode(flag) {
        this.isEnergySavingMode = flag;
        return this;
    }

    toJson() {
        return JSON.stringify(this);
    }

    /*
     * dump irremote coding according to current state
     *
     * @param {boolean} isHex dumps hex coding string is true,
     *                        otherwise dumps binary coding string
     *
     * @return {string} the encoding string
     */
    compile(isHex = true) {
        throw NotImplementedError("AirConditioner::dumpCommand() not implemented");
    }

}

module.exports = {
    AirConditioner,
    AirConditionerMode,
    AirConditionerWindSpeed
};
