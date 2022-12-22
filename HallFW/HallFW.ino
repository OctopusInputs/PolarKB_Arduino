/* 
This is a very early stage project currently and code is not final by any means
*/


#include <map>

// Define pins for the multiplexer
const int s0Pin = 18;
const int s1Pin = 19;
const int s2Pin = 20;
const int s3Pin = 21;
const int muxInput1= A8;

// Define an array to store the truth table values for the multiplexer
int truthTable[16][4] = {{0, 0, 0, 0},
                        {1, 0, 0, 0},
                        {0, 1, 0, 0},
                        {1, 1, 0, 0},
                        {0, 0, 1, 0},
                        {1, 0, 1, 0},
                        {0, 1, 1, 0},
                        {1, 1, 1, 0},
                        {0, 0, 0, 1},
                        {1, 0, 0, 1},
                        {0, 1, 0, 1},
                        {1, 1, 0, 1},
                        {0, 0, 1, 1},
                        {1, 0, 1, 1},
                        {0, 1, 1, 1},
                        {1, 1, 1, 1}};

// Set up an array to store the sensor readings
int sensorReadings[16];

// Set up a map to store the keymap
std::map<int, int> keymapMux1 = {{0, KEY_A}, {1, KEY_B}, {2, KEY_C}, {3, KEY_D},
                                 {4, KEY_F}, {5, KEY_G}, {6, KEY_H}, {7, KEY_H},
                                 {8, KEY_I}, {9, KEY_J}, {10, KEY_K}, {11, KEY_L},
                                 {12, KEY_M}, {13, KEY_N}, {14, KEY_O}, {15, KEY_P}};

std::map<int, int> actuationValues = {{0, 600}, {1, 600}, {2, 600}, {3, 600},
                                      {4, 600}, {5, 600}, {6, 600}, {7, 600},
                                      {8, 600}, {9, 600}, {10, 600}, {11, 600},
                                      {12, 600}, {13, 600}, {14, 600}, {15, 600}};

std::map<int, int> releaseValues = {{0, 550}, {1, 550}, {2, 550}, {3, 550},
                                    {4, 550}, {5, 550}, {6, 550}, {7, 550},
                                    {8, 550}, {9, 550}, {10, 550}, {11, 550},
                                    {12, 550}, {13, 550}, {14, 550}, {15, 550}};
                           

void setup() {
  // Set the multiplexer pins as outputs
  pinMode(s0Pin, OUTPUT);
  pinMode(s1Pin, OUTPUT);
  pinMode(s2Pin, OUTPUT);
  pinMode(s3Pin, OUTPUT);

  // Set the input and output pins as inputs and outputs, respectively
  pinMode(muxInput1, INPUT);

  // Initialize serial communication
  Serial.begin(9600);

}

void loop() {
   // Read the sensor readings from the multiplexer
for (int i = 0; i < 16; i++) {
    // Set the multiplexer channels using the truth table
    digitalWrite(s0Pin, truthTable[i][0]);
    digitalWrite(s1Pin, truthTable[i][1]);
    digitalWrite(s2Pin, truthTable[i][2]);
    digitalWrite(s3Pin, truthTable[i][3]);

    // Read the sensor on the current channel
    sensorReadings[i] = analogRead(muxInput1);
    
  }
       // Print the sensor readings to the serial monitor
  for (int i = 0; i < 16; i++) {
    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(sensorReadings[i]);
    
  }
  // Use the keymap and actuationValues to determine which keystrokes to send
  for (int i = 0; i < 16; i++) {
    if (sensorReadings[i] > actuationValues[i]) {
      Keyboard.press(keymapMux1[i]);
    } else if (sensorReadings[i] < releaseValues[i]) {
      Keyboard.release(keymapMux1[i]);
  }
}
}
