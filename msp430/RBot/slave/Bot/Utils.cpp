#include "Utils.h"

Utils::Utils() {}

Utils::~Utils() {}

unsigned char Utils::readDigit(HardwareSerial *serial) {
    int c;

    while ((c = serial->read()) == -1);     // no input

    if ('0' <= c && c <= '9') {
        c -= '0';
    } else if ('a' <= c && c <= 'z') {
        c = c - 'a' + 10;
    } else if ('A' <= c && c <= 'Z') {
        c = c - 'A' + 10;
    } else {
        /* TODO: <2018-06-06, forest9643, error> */
    }

    return (unsigned char) c;
}

unsigned long Utils::readUnsignedLong(HardwareSerial *serial) {
    unsigned long result = 0UL;
    for (char i = 0; i < (char) (sizeof(unsigned long)<<1); ++i) {

        // while ((c = serial->read()) == -1);     // read enough byte
        // 
        // // support hex
        // if ('0' <= c && c <= '9') {
        //     c -= '0';
        // } else if ('a' <= c && c <= 'z') {
        //     c = c - 'a' + 10;
        // } else if ('A' <= c && c <= 'Z') {
        //     c = c - 'A' + 10;
        // } else {
        //     [> TODO: <2018-06-06, forest9643, error> <]
        // }

        result <<= 4;
        result |= (unsigned long) Utils::readDigit(serial);
    }
    return result;
}

/*
 * TODO: <2018-06-06, forest9643,
 * just support 16 maximum command type at present>
 */
CommandType Utils::readCommandType(HardwareSerial *serial) {
    unsigned char commandType = readDigit(serial);

    switch (commandType) {
        case LED:
            return LED;
        case TEMPERATURE_SENSOR:
            return TEMPERATURE_SENSOR;
        case AIR_CONDITIONER:
            return AIR_CONDITIONER;
        case HEART_BEAT:
            return HEART_BEAT;
        default:
            return INVALID;
    }
}
