#include "./IRremote.h"
#include <Energia.h>
#include "Utils.h"
#include "CommandType.h"
#include "TemperatureSensor.h"

static CommandType gCommandType;

// control infrared ray
static IRsend gIrsend;
unsigned long gBeginningHalfPart;
unsigned long gEndingHalfPart;

// control led
int gRED_LED;
int gGREEN_LED;

// temperature sensor
TemperatureSensor gTemperatureSensor;

void setup() {
    // test turn off air-conditioner
    /* irsend.sendGree(0x8090040a, 0x00040008); */
    // 28090040a00040008

    Serial.begin(9600);

    pinMode(RED_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
}

void loop() {

    gCommandType = Utils::readCommandType(&Serial);

    switch (gCommandType) {
        case LED:
            gRED_LED = Utils::readDigit(&Serial);
            gGREEN_LED = Utils::readDigit(&Serial);

            if (!(gRED_LED == 0xf && gGREEN_LED == 0xf)) { // not lookup
                digitalWrite(RED_LED, (uint8_t)gRED_LED);
                digitalWrite(GREEN_LED, (uint8_t)gGREEN_LED);
            }
            Serial.print("LED:");
            Serial.print(digitalRead(RED_LED));
            Serial.println(digitalRead(GREEN_LED));
            break;
        case TEMPERATURE_SENSOR:
            Serial.print("SE_TP:");
            Serial.println(gTemperatureSensor.read());
            break;
        case AIR_CONDITIONER:
            gBeginningHalfPart = Utils::readUnsignedLong(&Serial);
            gEndingHalfPart = Utils::readUnsignedLong(&Serial);
            gIrsend.sendGree(gBeginningHalfPart, gEndingHalfPart);
            Serial.println("AC:OK");
            /* Serial.print(gBeginningHalfPart, HEX);
             * Serial.print(" ");
             * Serial.println(gEndingHalfPart, HEX);
             */
            break;
        case HEART_BEAT:
            Serial.println("HTBT:OK");
            break;
        default:
            Serial.println("ERR:invalid command");
            break;
    }
}
