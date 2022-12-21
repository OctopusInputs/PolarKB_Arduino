/* 
This is a very early stage project currently and code is not final by any means.
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
std::map<int, char> keymapMux1 = {{0, 'a'}, {1, 'b'}, {2, 'c'}, {3, 'd'},
                                 {4, 'e'}, {5, 'f'}, {6, 'g'}, {7, 'h'},
                                 {8, 'i'}, {9, 'j'}, {10, 'k'}, {11, 'l'},
                                 {12, 'm'}, {13, 'n'}, {14, 'o'}, {15, 'p'}};

std::map<int, int> actuationValues = {{0, 600}, {1, 600}, {2, 600}, {3, 600},
                                      {4, 600}, {5, 600}, {6, 600}, {7, 600},
                                      {8, 600}, {9, 600}, {10, 600}, {11, 600},
                                      {12, 600}, {13, 600}, {14, 600}, {15, 600}};
                           

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
    } else {
    Keyboard.release(keymapMux1[i]);
    }
  }
}
