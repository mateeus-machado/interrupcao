#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "hardware/pio.h"

#include "interrupcao.pio.h"

// Definições de pinos
#define LED_VERMELHO 13
#define BOTAO_A 6
#define BOTAO_B 5
#define MATRIZ 7

// Definições da matriz de LEDs e números
#define NUM_PIXELS 25

// Protótipo da função de interrupção
static void gpio_irq_handler(uint gpio, uint32_t events);

// Funções para controle da matriz de LEDs
uint32_t get_color(double r, double g, double b) {
    unsigned char R, G, B;
    R = r * 255;  // A intensidade do vermelho
    G = g * 0;    // Nenhuma intensidade de verde
    B = b * 0;    // Nenhuma intensidade de azul
    return (G << 24) | (R << 16) | (B << 8);  // Retorna a cor vermelha
}

void put_leds(uint* art, double* red, double* green, double* blue, uint32_t valor_led, PIO pio, uint sm) {
    for (int16_t i = 0; i < NUM_PIXELS; i++) {   
        if (i == 15 || i == 5) {
            int16_t aux = i;
            for (int16_t j = i + 4; j >= aux; j--, i++) {
                valor_led = get_color(red[24 - j], green[24 - j], blue[24 - j]);
                if (art[24 - j]) {
                    pio_sm_put_blocking(pio, sm, valor_led);
                } else {
                    pio_sm_put_blocking(pio, sm, 0);
                }
            }
            i--;
        } else {
            valor_led = get_color(red[24 - i], green[24 - i], blue[24 - i]);
            if (art[24 - i]) {
                pio_sm_put_blocking(pio, sm, valor_led);
            } else {
                pio_sm_put_blocking(pio, sm, 0);
            }
        }
    }
}

// Função para exibir números na matriz de LEDs
void exibir_numero(PIO pio, uint sm, uint contador) {
    double red[NUM_PIXELS] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
    double green[NUM_PIXELS] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    double blue[NUM_PIXELS] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    
    uint* numero;

    uint numero_0[25] = {
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1
    };

    uint numero_1[25] = {
        0, 0, 1, 0, 0,
        0, 1, 1, 0, 0,
        1, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        1, 1, 1, 1, 1
    };

    uint numero_2[25] = {
        1, 1, 1, 1, 1,
        0, 0, 0, 0, 1,
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 0,
        1, 1, 1, 1, 1
    };

    uint numero_3[25] = {
        1, 1, 1, 1, 1,
        0, 0, 0, 0, 1,
        1, 1, 1, 1, 1,
        0, 0, 0, 0, 1,
        1, 1, 1, 1, 1
    };

    uint numero_4[25] = {
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1,
        0, 0, 0, 0, 1,
        0, 0, 0, 0, 1
    };

    uint numero_5[25] = {
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 0,
        1, 1, 1, 1, 1,
        0, 0, 0, 0, 1,
        1, 1, 1, 1, 1
    };

    uint numero_6[25] = {
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 0,
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1
    };

    uint numero_7[25] = {
        1, 1, 1, 1, 1,
        0, 0, 0, 0, 1,
        0, 0, 0, 1, 0,
        0, 0, 1, 0, 0,
        0, 1, 0, 0, 0
    };

    uint numero_8[25] = {
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1
    };

    uint numero_9[25] = {
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1,
        0, 0, 0, 0, 1,
        1, 1, 1, 1, 1
    };
    
    switch (contador) {
        case 0: numero = numero_0; break;
        case 1: numero = numero_1; break;
        case 2: numero = numero_2; break;
        case 3: numero = numero_3; break;
        case 4: numero = numero_4; break;
        case 5: numero = numero_5; break;
        case 6: numero = numero_6; break;
        case 7: numero = numero_7; break;
        case 8: numero = numero_8; break;
        case 9: numero = numero_9; break;
        default: numero = numero_0; break;
    }

    // Atualiza os LEDs com a cor vermelha
    put_leds(numero, red, green, blue, 0, pio, sm);
}

// Função para piscar o LED vermelho 5 vezes por segundo
void piscar_led_vermelho() {
    static uint32_t last_toggle_time = 0;
    uint32_t current_time = to_us_since_boot(get_absolute_time());

    // 200ms para piscar 5 vezes por segundo
    if (current_time - last_toggle_time > 200000) {  
        last_toggle_time = current_time;  // Atualiza o tempo da última troca

        // Alterna o estado do LED (ON/OFF)
        static bool led_on = false;
        led_on = !led_on;
        gpio_put(LED_VERMELHO, led_on ? 1 : 0);  // Liga ou desliga o LED
    }
}

// Função de interrupção
static void gpio_irq_handler(uint gpio, uint32_t events) {
    static volatile uint32_t last_time = 0;
    static volatile int contador = 0;

    uint32_t current_time = to_us_since_boot(get_absolute_time());
    if (current_time - last_time > 200000) { // Debouncing
        last_time = current_time;

        // Ação de incrementar ou decrementar o contador
        if (gpio == BOTAO_A && contador < 9) {
            contador++;
        } else if (gpio == BOTAO_B && contador > 0) {
            contador--;
        }

        // Atualiza o display com o novo número
        exibir_numero(pio0, 0, contador);
    }
}

int main() {
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);

    gpio_init(BOTAO_A);
    gpio_set_dir(BOTAO_A, GPIO_IN);
    gpio_pull_up(BOTAO_A);

    gpio_init(BOTAO_B);
    gpio_set_dir(BOTAO_B, GPIO_IN);
    gpio_pull_up(BOTAO_B);

    // Configuração do clock para 128 MHz
    set_sys_clock_khz(128000, false);

    // Inicializa a comunicação com a serial
    stdio_init_all();

    // Inicializa o PIO e configura o contador
    uint offset = pio_add_program(pio0, &interrupcao_program);
    uint sm = pio_claim_unused_sm(pio0, true);
    interrupcao_program_init(pio0, sm, offset, MATRIZ);

    // Exibe o número inicial
    exibir_numero(pio0, sm, 0);

    // Configura as interrupções dos botões
    gpio_set_irq_enabled_with_callback(BOTAO_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(BOTAO_B, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    // Loop principal
    while (true) {
        // Chama a função para piscar o LED vermelho
        piscar_led_vermelho();

        // Pode adicionar qualquer outra lógica aqui, se necessário
    }

    return 0;
}
