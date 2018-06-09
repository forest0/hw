#ifndef UTILS_H
#define UTILS_H

#define __MSP430_HAS_USCI__
#include <HardwareSerial.h>
#include "CommandType.h"

/*
 * some utility functions defined here
 *
 */
class Utils {
private:

public:
    Utils ();
    ~Utils ();

    /*
     * \brief read a heximal digit from serial
     *
     * \param serial hardware serial
     *
     * \return a digit from 0 to f, both inclusive
     */
    static unsigned char readDigit(HardwareSerial *serial);

    /*
     * \brief read an unsigned long from serial
     *
     * \param serial hardware serial
     *
     * \return an unsigned long number
     *
     * NOTE: sizeof(unsigned long) == 4 in msp430g2553
     */
    static unsigned long readUnsignedLong(HardwareSerial *serial);

    /*
     * \brief read command type from serial
     *
     * \param serial hardware serial
     *
     * \return command type which defined in CommandType.h
     */
    static CommandType readCommandType(HardwareSerial *serial);
};

#endif /* UTILS_H */
