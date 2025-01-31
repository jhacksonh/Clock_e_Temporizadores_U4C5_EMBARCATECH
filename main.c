#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"

#define TIMER_ACTIVE_MS 3000
static const uint PINS_RGB[3] = {13, 12, 11}; // red, blue(amarelo), green
static int INDEX = 0;
struct repeating_timer timer;

static char *informations[3] = {
    "Sinal vermelho, não atravessar",
    "Sinal amarelo, atravessar com cuidado",
    "Sinal verde, atravessar"
};
static char *information = "";

void ConfigPins(uint pin, bool InorOut){
    gpio_init(pin);
    gpio_set_dir(pin, InorOut);
    gpio_put(pin, 0);
}

void Signal(){
    printf("Mudando Cor do Sinal...\n");
    information = informations[INDEX];
    for (int i = 0; i < 3; i++)gpio_put(PINS_RGB[i], i!=INDEX?0:1);
    INDEX = INDEX<2?INDEX+1:0;
}

bool repeating_timer_callback(struct repeating_timer *t) {
    Signal();
    return true;
}

int main(){
    stdio_init_all();

    for (int i = 0; i < 3; i++)ConfigPins(PINS_RGB[i],GPIO_OUT);
    Signal();
    add_repeating_timer_ms(TIMER_ACTIVE_MS, repeating_timer_callback, NULL, &timer);

    while (1){
        sleep_ms(1000);
        printf("%s\n",information);
    }
}
