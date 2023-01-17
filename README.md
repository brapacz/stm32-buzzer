# Buzzer library

## description

Library for beeping using single timer with 1 pwm channels for STM32. I used it on STM32F103.

* File `buzzer.c` and `buzzer.h` contains init and play functions,
* File `buzzer_tones.h` contains all notes from B0 do D#8,
* File `buzzer_examples.h` contains super mario theme in form of a table.

## setup

Create folder `ExternalLibs` in your project root directory and clone repository there:

```bash
git clone git@github.com:brapacz/stm32-buzzer.git my-project-path/ExternalLibs/Buzzer
```

or as externl module:

```bash
git submodule add --force git@github.com:brapacz/stm32-buzzer.git my-project-path/ExternalLibs/Buzzer
```

or just download zip archive and extract there:

```bash
cd ExternalLibs
wget https://github.com/brapacz/stm32-buzzer/archive/refs/heads/master.zip
unzip master.zip
rm -v master.zip
```

### System Workbench for STM32

Next go to project `properties`, then `C/C++ General/Paths and Symbols` on tab `Includes` and `Source Locations` add `my-project-path/ExternalLibs/Buzzer/src` directory

Go to CubeMX, choose any timer and channel and enable `PWM Generation CHx`. I used `TIM4` and `Channel 3`.
My parameter settings:

```
Counter:
	Prescaler (PRS - 16 bit value): 8-1
	Counter Mode: UP
	Counter Period (AutoReload Register - 16 bit value): 0xFFFF
	Internal Clock Divison (CKD): No Division
	auto-reload preload: disable

PWM Generation Channel3:
	Mode: PWM Mode 1
	Pulse (16 bit value): 50-1
	Fast Mode: Disable
	CH Polarity: High

GPIO tab:
	user label: BUZZER
	Maimum output speed: HIGH
```

Click `Generate code`. In `main.c` file, in matching sections add:

```C
/* Private includes */
#include "buzzer.h"
#include "buzzer_examples.h"
```

```C
/* USER CODE BEGIN PV */
Buzzer_HandleTypeDef hbuzzer;
```

```C
/* USER CODE BEGIN 0 */
Buzzer_InitTypeDef buzzerConfig;
buzzerConfig.channel = TIM_CHANNEL_3;
buzzerConfig.timer = &htim4;
buzzerConfig.timerClockFreqHz = HAL_RCC_GetPCLK2Freq(); // NOTE: this should be freq of timer, not frequency of peripheral clock
Buzzer_Init(&hbuzzer, &buzzerConfig);
Buzzer_Start(&hbuzzer);

const size_t songSize = sizeof(buzzer_mario_theme) / sizeof(buzzer_mario_theme[0]);
for (size_t i = 0; i < songSize; i++) {
	Buzzer_Note(&hbuzzer, buzzer_mario_theme[i].pitch);
	HAL_Delay(buzzer_mario_theme[i].duration * 15);
}
Buzzer_Note(&hbuzzer, 0);
```

## wiring

I used tiny speaker, resistor for protection and NPN transistor, it was loud enough to be noticable. It should also work with speaker directly wired between MCU pin and GND.

```
                                  ___ 3v3
                                   |
                                   |
                                   |
                                  _|_
                                  | |
                                  | |  100 Ohm resistor
                                  |_|
                                   |
                                   |
                                   |    __
                                   |___|  \
                                       |   | Buzzer/Speaker/Piezzo
                                    ___|   |
                                   |   |__/
                                   |
                                ___|__
            47 Ohm resistor    /   /  \
               __________     /  |/    \
 MCU pin ______|        |_____|__|     | S8050 NPN transistor
               |________|     |  |\    |
                              \  | ↘   /
                               \___|__/
                                   |
                                   |
                                   |
                                   |
                                   |
                                   V  GND
```
