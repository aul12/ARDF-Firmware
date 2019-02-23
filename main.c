#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdbool.h>


int main() {
    // Disable the interrupts
    cli();

    // Enable the interrupts
    sei();

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (true) {
    }
#pragma clang diagnostic pop
}
