# automatic_block

This is a demonstration of a simple sequence of automatic signals. It mimics the standard
British four-aspect signalling system.

**This code is for demonstration purposes only, it is not written to the standard required 
for safety critical systems and should not be used as such.**

The code is written for a Raspberry Pi Pico.

## Building

You will need `cmake` and `arm-none-eabi-gcc`.

Download the Raspberry Pi Pico SDK and the automatic_block source then enter the 
automatic_block source:

```
git clone https://github.com/sarrus/automatic_block
git clone https://github.com/raspberrypi/pico-sdk.git
cd automatic_block
```

Set the path to the Pico SDK:

```
export PICO_SDK_PATH=/path/to/pico-sdk
```

Initialise `cmake` and run the build:
```
cmake .
cmake --build .
```

This will generate `automatic_block.uf2` which can be loaded onto your Pico.

## Wiring

The `blocks` array in `main.c` indicates which pin is configured for which purpose. You
can modify this array if required.

`redPin`, `yellowPin`, `greenPin` and `secondYellowPin` can all be used to drive LEDs.
Remember that you will need to provide resistors to ensure that the LEDs receive the correct
current.

`circuitPin` can be used to form a simple track circuit. Connect this pin to one rail and
the other rail to ground. When the train passes over the circuit it will short the two
rails together which the Pico can detect.