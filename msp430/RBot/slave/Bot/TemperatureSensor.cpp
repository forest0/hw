#include "TemperatureSensor.h"
#include <msp430g2553.h>

/* TODO: <2018-06-06, forest9643
 * is it appropriate to put the initial code in constructor?>
 */
TemperatureSensor::TemperatureSensor() {
    ADC10CTL0 &= ~ENC;
    ADC10CTL0 = ADC10IE + ADC10ON + REFON + ADC10SHT_3 + SREF_1;
    ADC10CTL1 = CONSEQ_0 + ADC10SSEL_0 + ADC10DIV_3 + SHS_0 + INCH_10;
    __delay_cycles(30000);
    ADC10CTL0 |= ENC;
}

double TemperatureSensor::read() const {
    ADC10CTL0 |= ENC + ADC10SC; // Sampling and conversion start
    __bis_SR_register(CPUOFF + GIE); // LPM0 with interrupts enabled
    return ADC10MEM * 425.5 / 1024 - 277.7;
}

TemperatureSensor::~TemperatureSensor() {

}
