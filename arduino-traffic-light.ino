// First, we set up variables to refer to each digital pin
const int pinTrafficGreen = 2;
const int pinTrafficYellow = 3;
const int pinTrafficRed = 4;
const int pinCrosswalkGreen = 5;
const int pinCrosswalkRed = 6;
const int pinButtonPushSensor = 10;
const int pinPiezo = 11;

/* We initialize the leds and set the sensor pin to a internal pull up resistor and then we initialize the system state */
void setup()
{
    // Initialize the led pins as Outputs
    initLedPins();

    // Initialize the sensor pin as a internal pull up resistor
    pinMode(pinButtonPushSensor, INPUT_PULLUP);

    // Initialize the system state
    initializeOblig();
}

void loop()
{
    // Check if the button is pressed
    int buttonState = digitalRead(pinButtonPushSensor);
	if (buttonState == LOW) {
        // If Button is pressed, cycle the lights
        pushCrosswalkButton();
    }
    else{
        // Beep for zero point five seconds and sleep for one second
        piezoBeepCycle(500);
        delay(500);
        delay(500);
    }
}

/* Test that the piezo works in isolation */
void testPiezo() {
    tone(pinPiezo, 1000, 500);
}


/* Test at all the Leds can be turned on */
void testLeds() {
    digitalWrite(pinTrafficGreen, HIGH);
    digitalWrite(pinTrafficYellow, HIGH);
    digitalWrite(pinTrafficRed, HIGH);
    digitalWrite(pinCrosswalkGreen, HIGH);
    digitalWrite(pinCrosswalkRed, HIGH);
}

/* Test cycling the traffic light */
void testTrafficLight() {
    cycleTrafficLight();
}

/* Test the crosswalk feature in isolation */
void testCrosswalk() {
    activateCrosswalk();
}

/* Test both the traffic light and the crosswalk in sequence */
void testLightAndCrosswalk() {
    // We assume that the button is pushed for this test

    pushCrosswalkButton();
}

/*Initializes our PINs as OUTPUT pins*/
void initLedPins() {
    pinMode(pinTrafficGreen, OUTPUT);
    pinMode(pinTrafficYellow, OUTPUT);
    pinMode(pinTrafficRed, OUTPUT);
    pinMode(pinCrosswalkGreen, OUTPUT);
    pinMode(pinCrosswalkRed, OUTPUT);
    pinMode(13, OUTPUT);
}

/*Sets the input PIN to HIGH*/
void enableOutputPin(int pin) {
    digitalWrite(pin, HIGH);
}

/*Sets the input PIN to LOW*/
void disableOutputPin(int pin) {
    digitalWrite(pin, LOW);
}

/*Cycles from Green to Yellow after 2 seconds, then Red after 1 more second. 
*/
void cycleTrafficLight() {
    enableOutputPin(pinTrafficGreen);
    delay(2000);
    disableOutputPin(pinTrafficGreen);
    enableOutputPin(pinTrafficYellow);
    delay(1000);
    disableOutputPin(pinTrafficYellow);
    enableOutputPin(pinTrafficRed);
}

/*Sets the crosswalk light to green and initiates a beeping sequence before cycling back to red.

After 6 seconds, it the green light starts blinking to signal the end of the "walk" phase.
*/
void activateCrosswalk() {
    // First, Turn the light to green
    disableOutputPin(pinCrosswalkRed);
    enableOutputPin(pinCrosswalkGreen);

    // Initialize the timer variables
    int greenLightDurationMs = 6000;
    int piezoBeepCycleMs = 250;
    int piezoBeepCycles = greenLightDurationMs / piezoBeepCycleMs;

    // Calls piezoBeepCycle() an "piezoBeepCycles" amount times. 
    for (int i = 0; i < piezoBeepCycles; i++) {
        piezoBeepCycle(125);
    }

    // After 6 seconds, green man will blink for 0.5s 3 times.
    for (int i = 0; i < 3; i++)
    {
        disableOutputPin(pinCrosswalkGreen);
        delay(500);
        enableOutputPin(pinCrosswalkGreen);
        delay(500);
    }

    // Reset the light state
    disableOutputPin(pinCrosswalkGreen);
    enableOutputPin(pinCrosswalkRed);
}

/*Beeps for halftimeMs (miliseconds) and stays silent for halftimeMs */
void piezoBeepCycle(int halftimeMs) {
    tone(pinPiezo, 50, halftimeMs);
    delay(halftimeMs); // wait for tone to finish, since tone() is non-blocking https://www.arduino.cc/reference/en/language/functions/advanced-io/tone/
    delay(halftimeMs);
}

/*Simulates the full system in motion when the crosswalk button is pressed.

Cycles the traffic light from green to red and waits 1s, then activates the crosswalk cycle function.
Afterwards, the traffic light cycles from red to yellow to green and cycles the crosswalk light to red.
*/
void pushCrosswalkButton() {
    // Turn on internal led to signal that the button press is registered.
    enableOutputPin(13);

    cycleTrafficLight();
    delay(1000); // Wait 1s after light turns red before activating crosswalk

    // Disable the internal LED.
    disableOutputPin(13);

    activateCrosswalk();
    
    // Once the crosswalk light is red, traffic light cycles to yellow for 1000ms and then green
    disableOutputPin(pinTrafficRed);
    enableOutputPin(pinTrafficYellow);
    delay(1000);
    disableOutputPin(pinTrafficYellow);
    enableOutputPin(pinTrafficGreen);
}

/*Sets the crosswalk light to red and the traffic light to green.*/
void initializeOblig() {
    enableOutputPin(pinTrafficGreen);
    enableOutputPin(pinCrosswalkRed);
}