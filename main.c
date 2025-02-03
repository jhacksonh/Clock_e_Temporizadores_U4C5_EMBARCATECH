#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"

#define TIMER_ACTIVE_MS 3000 // Define o tempo em milissegundos para troca de cor
static const uint PINS_RGB[3] = {13, 12, 11}; // Define os pinos para os LEDs RGB (vermelho, azul/amarelo, verde)
static int INDEX = 0; // Índice para alternar entre as cores do sinal
struct repeating_timer timer; // Estrutura para o temporizador repetitivo

// Mensagens associadas a cada cor do semáforo
static char *informations[3] = {
    "Sinal vermelho, não atravessar",
    "Sinal amarelo, atravessar com cuidado",
    "Sinal verde, atravessar"
};
static char *information = ""; // Ponteiro para armazenar a mensagem atual

// Função para configurar um pino como entrada ou saída
void ConfigPins(uint pin, bool InorOut){
    gpio_init(pin); // Inicializa o pino
    gpio_set_dir(pin, InorOut); // Define a direção do pino (entrada ou saída)
    gpio_put(pin, 0); // Define o pino como nível baixo (desligado)
}

// Função que altera a cor do semáforo e a mensagem correspondente
void Signal(){
    information = informations[INDEX]; // Atualiza a mensagem com base no índice atual
    for (int i = 0; i < 3; i++) gpio_put(PINS_RGB[i], i != INDEX ? 0 : 1); // Liga o LED correspondente e desliga os outros
    INDEX = INDEX < 2 ? INDEX + 1 : 0; // Atualiza o índice para a próxima cor
}

// Callback do temporizador que chama a função Signal periodicamente
bool repeating_timer_callback(struct repeating_timer *t) {
    printf("Mudando Cor do Sinal...\n"); // Exibe mensagem no console
    Signal(); // Chama a função que altera o sinal
    return true; // Retorna verdadeiro para manter o temporizador ativo
}

int main(){
    stdio_init_all(); // Inicializa a comunicação serial

    for (int i = 0; i < 3; i++) ConfigPins(PINS_RGB[i], GPIO_OUT); // Configura os pinos dos LEDs como saída
    Signal(); // Configura o primeiro estado do semáforo
    add_repeating_timer_ms(TIMER_ACTIVE_MS, repeating_timer_callback, NULL, &timer); // Inicia o temporizador repetitivo

    while (1){
        printf("%s\n", information); // Exibe a mensagem do semáforo atual no console
        sleep_ms(1000); // Aguarda 1 segundo antes de imprimir novamente
    }
}
