# Digital Etch A Sketch Final Project

## Project Overview

This project is a digital version of an Etch A Sketch built with an Arduino, two potentiometers, an SSD1309 OLED display, and an MPU6500 IMU. The two potentiometers control the X and Y drawing position on the OLED screen. The IMU detects a double-shake gesture, which clears the drawing from the display.

The project recreates the basic behavior of a physical Etch A Sketch: two knobs control drawing movement, and shaking the device erases the screen. The Arduino reads the two potentiometers, maps the analog readings to OLED pixel coordinates, draws a continuous line from the previous cursor position to the current cursor position, and clears the display when two shakes are detected within a two-second window.

## Features

- X-axis drawing control using a potentiometer on analog pin A0
- Y-axis drawing control using a potentiometer on analog pin A1
- 128 x 64 SSD1309 OLED drawing display
- Continuous line drawing using previous and current cursor positions
- Double-shake screen clearing using an MPU6500 IMU
- Analog input smoothing to reduce cursor jitter
- Startup and reset logic to prevent unwanted lines from being drawn

## Hardware Used

| Component | Purpose |
|---|---|
| Arduino Uno or compatible board | Main microcontroller |
| SSD1309 128 x 64 OLED display | Drawing display |
| Two potentiometers | X and Y drawing controls |
| MPU6500 IMU | Shake detection |
| Breadboard and jumper wires | Circuit connections |
| USB cable | Power and code upload |

## Wiring Summary

| Component | Arduino Pin | Purpose |
|---|---:|---|
| X Potentiometer Signal | A0 | Horizontal drawing control |
| Y Potentiometer Signal | A1 | Vertical drawing control |
| OLED SDA | SDA | I2C data |
| OLED SCL | SCL | I2C clock |
| MPU6500 SDA | SDA | I2C data |
| MPU6500 SCL | SCL | I2C clock |
| VCC pins | 5 V or 3.3 V depending on module | Power |
| GND pins | GND | Ground reference |

## Software Libraries

The Arduino sketch uses the following libraries:

- `Wire`
- `U8g2`
- `FastIMU`

## Repository Contents

```text
Digital-Etch-A-Sketch-Final-Project/
|
|-- README.md
|-- code/
|   |-- etch_a_sketch.ino
|-- report/
|   |-- final_project_report.pdf
|-- images/
|   |-- After_reset.JPG
|   |-- Drawing.JPG
|   |-- Full_Circuit.JPG
|   |-- OLED_Connection.JPG
|   |-- Potentiometers_IMU.JPG
|-- diagrams/
|   |-- Block Diagram.png
|   |-- Flow Diagram.png
|-- testing/
    |-- shake_test_notes.txt
    |-- potentiometer_test_notes.txt
```

## How to Run

1. Open `code/etch_a_sketch.ino` in the Arduino IDE.
2. Install the required libraries: `U8g2` and `FastIMU`.
3. Connect the OLED and MPU6500 through the I2C SDA and SCL lines.
4. Connect the X and Y potentiometer signal pins to A0 and A1.
5. Select the correct Arduino board and COM port.
6. Upload the code.
7. Use the two potentiometers to draw on the OLED.
8. Shake the project twice within two seconds to clear the screen.

## Code Structure

The code is organized into separate sections for OLED setup, IMU setup, pin definitions, drawing state, shake detection, helper functions, setup, and the main loop.

| Function | Purpose |
|---|---|
| `readSmooth(int pin)` | Averages eight analog readings to reduce potentiometer jitter |
| `clearDrawing(int x, int y)` | Clears the OLED and resets the previous cursor position |
| `doubleShakeDetected()` | Uses IMU acceleration data to detect two shakes within a time window |
| `setup()` | Initializes serial communication, I2C, OLED, and IMU |
| `loop()` | Reads inputs, checks for shake-clear, draws lines, and updates the OLED |

## Testing Summary

The potentiometers were tested by turning each knob and verifying that the cursor moved horizontally and vertically on the OLED. The OLED was tested by drawing connected line segments. The IMU was tested by shaking the project and confirming that the display cleared only after a deliberate double shake.

## Group Member Contributions

| Member | Contributions |
|---|---|
| Tadhg Cronin | Arduino code, potentiometer drawing control, OLED display integration, IMU shake-clear logic, testing, report writing, repository organization |

## Final Result

The final system successfully creates a digital Etch A Sketch. The potentiometers provide drawing control, the OLED displays a continuous drawing path, and the MPU6500 IMU allows the user to clear the screen using a double-shake gesture.
