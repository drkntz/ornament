/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC16F18325
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include "dotstar/dotstar.h"

// function prototypes
void dotstar_write_brgb(uint8_t brightness, uint8_t red, uint8_t green, uint8_t blue);
void delay_ms(uint16_t ms);
void _demo_animation(void);
uint8_t num_leds = 16;

void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
    SPI1_Open(0);
    uint8_t dir = 1;
    uint8_t blue = 1;
    uint8_t state = 0;
    uint8_t loops = 0;
    uint8_t i;
    dotstar_setup();
    dotstar_set_brightness(31); // max brightness is 31
    
    dotstar_clear();
    dotstar_set_pixel(0, 0xAA, 0xAA, 0xAA);
    
    dotstar_show();
    
    
    
    while(0)
    {
        delay_ms(10);
        dotstar_show();
    }
    
    while (1)
    {
        _demo_animation();
    }
}

// for demonstration
void _demo_animation(void)
{
    static uint16_t numloops = 0;
    static uint8_t state = 0;
    static uint8_t i;
    
    switch(state)
    {
        case 0:
//            for(i = 0; i < num_leds/3; i++)
//            {
//                dotstar_set_pixel(i, 0xFF, 0x00, 0x00);
//            }
//            for(; i < 2*num_leds/3; i++)
//            {
//                dotstar_set_pixel(i, 0xFF, 0xFF, 0xFF);
//            }
//            for(; i < num_leds; i++)
//            {
//                dotstar_set_pixel(i, 0x00, 0x00, 0xFF);
//            }
//            dotstar_show();
//            delay_ms(2000);
//            dotstar_set_all(0xFF, 0x00, 0x00);
//            dotstar_show();
//            delay_ms(500);
//            dotstar_set_all(0x00, 0xFF, 0x00);
//            dotstar_show();
//            delay_ms(500);
//            dotstar_set_all(0x00, 0x00, 0xFF);
//            dotstar_show();
//            delay_ms(500);
//            dotstar_clear();
//            dotstar_show();
//            delay_ms(500);
            state++;
        break;
        case 1: // rotate 4 dots clockwise
            spiral_clockwise();
            delay_ms(75);
            numloops++;
            if(numloops == 150)
            {
                numloops = 0;
                state ++;
            }
        break;
        case 2: // rotate 4 dots counterclockwise
            spiral_counterclockwise();
            delay_ms(20);
            numloops++;
            if(numloops == 50)
            {
                numloops = 0;
                state ++;
            }
        break;
        case 3: // snake clockwise
            dotstar_chase();
            delay_ms(75);
            numloops++;
            if(numloops == 150)
            {
                numloops = 0;
                state ++;
            }
        break;
        case 4: // fade rainbow
            dotstar_colorfade();
            delay_ms(10);
            numloops++;
            if(numloops == 1500)
            {
                numloops = 0;
                state ++;
            }
        break;

            
        break;
            default:
                state = 0;
                numloops = 0;
            break; 
        }
}

void dotstar_write_brgb(uint8_t brightness, uint8_t red, uint8_t green, uint8_t blue)
{
    uint8_t start_packet[4] = {0x00};
    uint8_t end_packet[4] = {
      0xFF,
      0xFF,
      0xFF,
      0xFF 
    };
    uint8_t led_frame[4] = {
      brightness | 0xE0, // brightness, has to start with 111
      blue,
      green,
      red
    };
    uint8_t i;
    
    SPI1_WriteBlock(start_packet, 4);
    for(i = 0; i < num_leds; i++)
    {
        SPI1_WriteBlock(led_frame, 4);
    }
    SPI1_WriteBlock(end_packet, 4);
}

void delay_ms(uint16_t ms)
{
    while(ms)
    {
        CLRWDT();
        __delay_ms(1);
        ms--;
    }
}


// topcon's color fade stuff
//
//        switch(state)
//        {
//                case 0:
//                    blue = 1;
//                    loops ++;
//                    if(loops == 0)
//                    {
//                        state ++;
//                    }
//                    break;
//            case 1:
//                blue = 32;
//                loops ++;
//                if(loops == 0)
//                {
//                    state ++;
//                    blue = 0;
//                }
//                break;
//            case 2:
//                    if(dir == 1)
//                    {
//                        blue ++;
//                    }
//                    else
//                    {
//                        blue --;
//                    }
//
//                    if(blue <= 1)
//                    {
//                        dir = 1; // go up
//                    }
//
//                    else if (blue >= 32)
//                    {
//                        dir = 0; // go down
//                    }
//                loops++;
//                if(loops == 0)
//                    state = 0;
//                break;
//                        
//        }
//        
//                
//        for(i = 0; i < num_leds; i++)       
//        {
//            if(i%2) dotstar_set_pixel(i, 0x00, 0x00, blue);
//        }
//       
//        dotstar_show();
//        __delay_ms(50);
