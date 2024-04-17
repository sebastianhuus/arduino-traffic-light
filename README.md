# Arduino Traffic Light

This project contains the source code for an Arduino-based traffic light system. It attempts to simulate a traffic light through this summarized use-case:
1. User presses button to trigger traffic light.
2. Traffic light turns yellow, then red, stopping cars. 
3. Traffic light shows green for pedestrians and beeps while active. Ends cycle with blinking to signal that the light will turn red soon.
4. Traffic light turns yellow, then red.

## Setup: Breadboard and Arduino
![Arduino project board](image.jpg)

## Setup (VS Code)
To build the code onto an Arduino board, I used the VS Code extension. 

1. Open the main directory. Ensure that it is named "arduino-traffic-light". Otherwise, the Arduino extension won't generate the `c_cpp_properties.json` file.
2. Run the command `Arduino: Initialize`.
3. Select `arduino-traffic-light.ino` as the base file
4. Select your Arduino board. In my case I'm using an Arduino Uno.

## Usage

Once the code is uploaded to your Arduino board, the traffic light system will start running automatically. It'll wait for the pushbutton to be pressed before triggering a crosswalk cycle. 
