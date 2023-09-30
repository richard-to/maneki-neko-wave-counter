# Maneki Neko Wave Counter

Have you ever wondered how many waves a Maneki Neko performs in a full day of work? Or have you ever been worried that your Maneki Neko has been slacking off? Well...now you can know the answer to these questions and more. 

This simple Arduino project uses an LCD shield and IR sensor to watch your Maneki Neko work day and night. 

Our formula for counting waves is a scientifically proven algorithm to make sure your Maneki Neko is performing perfect wave every time. And as an added bonus, our LCD is programmed with a full rainbow of background colors.

## Features

The features are pretty limited.

1. Counts maneki neko waves. The IR sensor needs to be placed perpendicular to the end
   of the paw. The `WAVE_DOWN_DISTANCE_CM` and `WAVE_UP_DISTANCE_CM` constants will need
   to be adjusted based on the maneki size's size. A wave is counted as a complete down
   and up motion.
2. The LCD background can be toggled by clicking the select button on the LCD Shield.
   The available colors can be adjusted by modifying the `colors` array.

## Components

- Sharp GP2Y0A41SKOF IR Sensor (4cm - 30cm)
  - Mine came with a JST Connector
-  Arduino UNO Rev3 (or compatible board)
-  DF Robot - I2C RGB Backlight LCD 16x2 Display Module for Arduino
   - I bought the shield because I wanted something simple (i.e. no soldering), but it
     should be possible to find a non-shield version of the LCD display module.
- 3 M/F jumper wires for IR Sensor
  - Analog pin
  - Ground
  - Power
- Maneki Neko
  - Can buy from Ebay

## Wiring 

The wiring is pretty straightforward. All we need to do is connect the Sharp IR Sensor
to the Arduino.

The Sharp IR Sensor has three pins:

- Analog pin to receive sensor output
- Power
- Ground

![Sharp IR Sensor to Arduino wiring](https://github.com/richard-to/maneki-neko-wave-counter/assets/539889/37e39d9c-4eee-410d-a40d-002e31134ceb)

To connect the Sharp IR sensor to the Arduino, we need to connect the wires to the DF
Robot LCD Shield which exposes multiple pins for sensors. We will use the A1 pin, but
you can also use other analog pins.

![Sharp IR Sensor to Arduino wiring side view](https://github.com/richard-to/maneki-neko-wave-counter/assets/539889/15167d48-0a6f-4b9b-aa8f-d4f0f6c2dc86)
