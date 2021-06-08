# ECE148 LED Board

A PCB that arranges WS2812b individually addressable RGB LEDs in a rectangle underneath a Jetson Nano to give it a swank gaming-PC aesthetic.
Designed for [UCSD's ECE148 final project by Team 1, SP21](https://guitar.ucsd.edu/maeece148/index.php/2021SpringTeam1).

<img width=400 src="media/led_board_demo.gif"/>

## PCB Overview

This PCB was hastily designed and is not my finest work, due to the time constraint we faced and the
fact that turnaround times for PCBs take a few days unless one pays a small fortune.

The PCB was designed in [KiCad](https://www.kicad.org/).

**Features:**
- STM32 F103C8T6 Microcontroller
- 10-pin SWD debug header
- JST-PH power connector with MIC5219 3V3 LDO Regulator
- Power LED
- Input voltage range from 3.7 V to 5V
- 16x WS2812b (aka Neopixels) arranged in a rectangle

**Absent Features**

I mention these not to roast myself (well kinda), but as a disclaimer to those looking at my design 
as reference for theirs. As I mentioned, I was on a time crunch so I couldn't afford the time to make this
a good-quality PCB. The following features should be included in a good design:
- Reset Pushbutton
- Generic I/O Breakouts
- Generic Button/LED for testing
- Testpoints for signals/power

## Firmware Overview

I used Michael Tien's STM32 code for [driving WS2812B LEDs using SPI over DMA](https://michaeltien8901.github.io/stm32/2018/07/19/Using-STM32-SPI-For-LED-STRIP.html)

Porting his code was easy. I created a new STM32CubeMX project for an STM32F103C8T6 microcontroller,
enabled the SPI1 peripheral, added a DMA channel for it, and set the clock as he described.

Then I automatically generated the code, and copied over Tien's helper functions from his `main.c` file,
and it worked like a charm. His functions are very straightforward to use, so thanks!

## Programming the board

(TODO Pictures)

I dislike using clunky IDEs unless I absolutely have to (i.e. for large projects). So I setup my CubeMX
project to use a Makefile, and use `make` to compile the code. Then I use my STLink V3-SET debug adapter
to flash the code, though any ST-Link probe that has a mini 10-pin cable will do. A quick guide on how
I flash STM32 code is on my [CubeProgrammer TechNotes](https://github.com/Ayilay/dotfiles/blob/master/techNotes/CubeProgrammer.md)
