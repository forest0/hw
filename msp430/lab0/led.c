#include <msp430x20x3.h>

int main(void) {

    WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer

    P1DIR |= 0x01;                            // Set P1.0 to output direction

    for (;;) {

        volatile unsigned long i;

        P1OUT ^= 0x01;                          // Toggle P1.0 using exclusive-OR

        i = 99999;                              // Delay

        do {
            i--;
        } while (i != 0);

    }

}
