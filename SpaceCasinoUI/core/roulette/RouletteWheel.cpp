#include "RouletteWheel.h"
#include <cstdlib>
#include <ctime>

int RouletteWheel::spin() {
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned int>(time(NULL)));
        seeded = true;
    }
    return rand() % 37;
}

Color RouletteWheel::getColor(int number) {
    if (number == 0) return Color::Green;

    int reds[] = { 1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36 };
    for (int r : reds) {
        if (r == number) {
            return Color::Red;
        }
    }
    return Color::Black;
}
