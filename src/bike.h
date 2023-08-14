#include <iostm8s003f3.h>
#include <stdint.h>

#define ANTIDREBEZG 10
#define POVOROT_INTERVAL 10 * 8
#define BLINK_SWITCH_INTERVAL POVOROT_INTERVAL * 24

void bike_init();
void bike_loop();

void frontlight_process();
void backlight_process();

typedef enum
    {
        PRESSED,
        UNPRESSED
    }buttonState;

typedef enum
    {
        LIGHT_OFF,
        LIGHT_ON
    }lightState;

class button
    {
        public:
        button(uint8_t *x,uint8_t y){IDR=(uint8_t*)x; PIN=y;};
        buttonState state;
        uint8_t bounce_cnt;
        uint16_t counter;
        uint8_t *IDR;
        uint8_t PIN;
        void button_process();
    };

class lighter
    {
        public:
        lighter(){};
        lighter(uint8_t *x,uint8_t y){ODR=(uint8_t*)x; PIN=y;};
        lightState state;
        uint8_t blink;
        uint8_t *ODR;
        uint8_t PIN;
        uint16_t counter;
        inline void light_on() { *ODR |= 1<<PIN; };
        inline void light_off() { *ODR &= ~(1<<PIN); };
        inline void light_toggle() {*ODR ^= (1<<PIN);};
        void povorotlight_process(button*);
    };
