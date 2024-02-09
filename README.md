# Digital scales for ESP32 using HX711

The HX711 is an 24 bit amplifier and ADC that can read load cells.  This can be used for digital scales.  This 
repository uses the ESP32 (NodeMCU-32s) and the ESP-IDF.

The code is based off the [HX711_IDF](https://github.com/akshayvernekar/HX711_IDF) project.


## Building

This is built on Linux using VS Code and Dev Containers.  When opening in the container you should have access to the
ESP-IDF and should be able to build, flash and monitor using the VS Code tooling.

## Configuration

The GPIO pins can be set in `hx711.c`:

```C
static gpio_num_t GPIO_PD_SCK = GPIO_NUM_15; // Serial Clock Pin
static gpio_num_t GPIO_DOUT = GPIO_NUM_14;	 // Serial Data Pin
```