# STM32 Audio Direction Locator

In my second year of studies, I developed a Sound Localisation device that detects the incoming direction of sudden loud noises. This was created as part of a streetlight that could be used in combination with other streetlights to triangulate noise nuisance within a city. The device consists of two MAX4466 microphone modules connected to a STM32 development board that uses signal processing techniques that were implemented using the Arduino Framework.

## Hardware

- MAX4466 microphone modules
- STM32F103C8T6 (Blue Pill)


## Features

- Cross-correlation algorithm to determine the receiving time difference of a specific audio sample between the two microphones.
- Uses TDOA (Time Difference of Arrival) to calculate the incoming direction of the noise
- High-frequency sampling using Direct Memory Access (DMA)
