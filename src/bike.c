#include "bike.h"

lighter backlight((uint8_t*)&(PC_ODR),4);;
lighter frontlight((uint8_t*)&(PC_ODR),5);
lighter leftlight((uint8_t*)&(PC_ODR),3);
lighter rightlight((uint8_t*)&(PA_ODR),3);

button left_btn((uint8_t*)&(PD_IDR),3);
button right_btn((uint8_t*)&(PC_IDR),7);
button front_btn((uint8_t*)&(PD_IDR),2);
button back_btn((uint8_t*)&(PC_IDR),6);

uint32_t tickstart;

void delay(uint32_t t){t*=1000;while (t--);}


void bike_init()
    {            

        //init INPUTS
        PD_CR1_bit.C12 = 1; //Pullup PD2
        PC_CR1_bit.C17 = 1; //Pullup PC7
        PC_CR1_bit.C16 = 1; //Pullup PC6
        PD_CR1_bit.C13 = 1; //Pullup PD3
        
        //init OUTPUTS
   
        PC_DDR_bit.DDR4 = 1;
        PC_CR1_bit.C14= 1 ;//PC4 backlight
        PC_DDR_bit.DDR5 = 1;
        PC_CR1_bit.C15 = 1;//PC5 frontlight
        PC_DDR_bit.DDR3 = 1;
        PC_CR1_bit.C13 = 1;//PC3 leftlight
        PA_DDR_bit.DDR3 = 1;
        PA_CR1_bit.C13 = 1;//PA3 rightlight
        
        CLK_CKDIVR_bit.HSIDIV = 3;
        CLK_CKDIVR_bit.CPUDIV = 4;//Decrease CPU freq
        CLK_PCKENR1 = 0;
        CLK_PCKENR2 = 0;//disable peripherals
                
    };


void bike_loop()
    {
        left_btn.button_process();
        right_btn.button_process();
        front_btn.button_process();
        back_btn.button_process();
        
        backlight_process();
        frontlight_process();
        leftlight.povorotlight_process(&left_btn);
        rightlight.povorotlight_process(&right_btn);
        
    };


void button::button_process()
    {
        if (state!=(*IDR>>PIN & 1))
                counter++;
        else
            counter=0;
        
        if (counter>ANTIDREBEZG)
            state = (buttonState)(*IDR>>PIN & 1);
    }

void backlight_process()
    {
        if (back_btn.state==PRESSED)
            {
                backlight.state = LIGHT_ON;
                backlight.light_on();
            }
        else
            {
                backlight.light_off();
                backlight.state = LIGHT_OFF;
            }
    }

void frontlight_process()
    {
        if (front_btn.state==PRESSED)
            {
                frontlight.state = LIGHT_ON;
                frontlight.light_on();
            }
        else
            {
                frontlight.light_off();
                frontlight.state = LIGHT_OFF;
            }
    }

void lighter::povorotlight_process(button *btn)
    {
        if (btn->state == PRESSED)
            {
                if (counter++>POVOROT_INTERVAL)
                    {
                        light_toggle();
                        counter=0;
                    }
            }
        else if (btn->state == UNPRESSED)
            {
                light_off();
            }
        
        if (*ODR & 1<<PIN)
            state = LIGHT_ON;
        else
            state = LIGHT_OFF;
    }