#ifndef COMMANDTYPE_H
#define COMMANDTYPE_H

enum CommandType {

    /*
     *     this command is for control the LEDs on the board
     *
     *     LED supports two kink of command: set and get,
     *     both of them are encoded with 3 digit, the first digit is
     *     the enum value of LED defined here
     *
     *     the remaining two digits are used to control RED_LED and GREEN_LED,
     *     note that RED_LED is controlled by second digit and
     *     GREEN_LED is controlled by third digit
     *         set command to set the status of LED
     *             format:     0xx, x can be 0 or 1, digit 0 for off and digit 1 for on
     *                         e.g. 010 means set RED_LED on and GREEN_LED off
     *
     *         get command to lookup the status of LED
     *             format:     it is always 0ff
     *
     *
     *      response message to master
     *          format:     "LED:xx",  x can be 0 or 1, 0 for off and 1 for on
     *                      the first  x represents RED_LED
     *                      the second x represents GREEN_LED
     *
     *          e.g. "LED:10" represent: currently, RED_LED is on and GREEN_LED is off
     */
    LED,

    /*
     *      this command is for reading the temperature sensor
     *
     *      the command is encoded with just one digit 1,
     *      which is the enum value of TEMPERATURE_SENSOR defined here
     *
     *
     *      response message to master
     *          format:     "SE_TP:a_float_value"
     *                      SE_TP is short for SENSOR_TEMPERATURE
     *                      a_float_value is the temperature value in centigrade degree
     */
    TEMPERATURE_SENSOR,

    /*
     *      this command is for control the air conditioner
     *
     *      the command is encoded with 17 digits, which can be divided into 2 parts
     *
     *      the first part contains just one digit, which is the enum value of
     *      AIR_CONDITIONER defined here
     *
     *      the second part contains 16 digits, which represents the control code
     *      of the air conditioner used by the infrared module
     *
     *
     *      response message to master
     *          format:     "AC:OK"
     *                      AC is short for AIR_CONDITIONER
     *                      here a OK just means slave has received
     *                      the command to control air conditioner,
     *                      but whether the air conditioner has received
     *                      the infrared signal or not is NOT guaranteed
     */
    AIR_CONDITIONER,

    /*
     *      this command is for the master to check the salve is connected
     *
     *      the command is encoded with one digit, which is the enum value of
     *      HEART_BEAT defined here
     *
     *
     *      response message to master
     *          format:     "HT_BT:OK"
     *                      HT_BT is short for HEART_BEAT,
     *                      OK means slave has received the message from the master
     */
    HEART_BEAT,

    /*
     *      invalid command
     *
     *      to indicate that slave does NOT understand master's intention
     *
     *
     *      response message to master
     *          format:     "ERR:msg"
     *                      ERR is short for ERROR,
     *                      the followed msg can be a string to indication what happened
     */
    INVALID
};

#endif /* COMMANDTYPE_H */
