/*
*** IMPORTANT ***

* Make sure that you change the definitions POWER, 
* CHANNEL_UP and CHANNEL_DOWN to the ones that*
* recorded in the 3rd step 

*** IMPORTANT***
*/

#include <IRremote.h> // Imports the IR Remote Library *You need to have it installed before this sketch can function
#include <Servo.h> // Imports the Servo Library, don't worry, It's already built into the Arduino IDE

#define FAN_PIN 11 // Define the pin that controls the fan
#define IR_PIN 3 // Define the pin that receives data from the IR sensor
#define SERVO_PIN 2
#define POWER 47418 // Stores the IR code of the "Power" button on your remote 
#define CHANNEL_UP 2326 // Stores the ir code of the "Channel Up" button
#define CHANNEL_DOWN 34780 // Stores the ir code of the "Channel Down" button
#define LED_PIN 13 // Access the internal LED
#define FAN_SPEED 255 // A number ranging from 0 - 255 t

int off = false;  // Initialize a variable that contains the state of the fan, on or off 
IRrecv irrecv(IR_PIN); // Create an IR receiver object
decode_results results; // Use the builtin decode_results function to return a human-readable value
Servo fanservo; // Create a servo object named fanservo
int pos = 90; // Center the Servo

void setup(){ // Initialize the setup() function
    pinMode(LED_PIN,OUTPUT); //
    pinMode(FAN_PIN,OUTPUT); // Make sure that the Arduino knows whether the LED pin, Fan pin and IR pin are for input or output
    pinMode(IR_PIN,INPUT);       //
    
    Serial.begin(9600); // Start serial communcations
    irrecv.enableIRIn(); // Start the receiving IR results
    fanservo.attach(SERVO_PIN);
    fanservo.write(pos);
} // End the setup() function

void loop(){ // Initialize the loop() function
  delay(10); // Let the servo and IR receiver catch up with the Arduino
  fanservo.write(pos); // Write the servo to the correct position
  if(off == false){ // If the fan is supposed to be on
    analogWrite(FAN_PIN,FAN_SPEED); // Turn it on
  }
  else{ // Otherwise
    analogWrite(FAN_PIN,0); // Turn it off
  }

  if(irrecv.decode(&results)) { // If there is an IR code available
      unsigned int value = results.value; // Set it equal to the unsigned integer value
      if(value == POWER){ // If the value of the ir code is the same as the previously defined POWER code
          Serial.println("Power pressed"); // Tell the serial monitor
          if(off == true){ // If the fan is off at the time of receiving
              off = false; // Turn it on
          }
          else{ // Otherwise
              off = true; // Turn it off
          }
      }
      else if(value == CHANNEL_UP){
            Serial.println("Channel Up pressed");
            Serial.print("Pos: ");
            Serial.println(pos);
            if(pos < 176) {pos += 4;}
      }
      else if(value == CHANNEL_DOWN){
            Serial.println("Channel Down pressed");
            Serial.print("Pos: ");
            Serial.println(pos);
            if(pos > 4) {pos -= 4;}  
      }
      
      irrecv.resume(); // Open the 
      
  }
}// End the loop() function

/*
Troubleshooting:

      - The fan speed doesn't change when I hit the "volume down/up" buttons
          - Are you sure that you have the correct IR code for each of your buttons?
          - Do you have the latest version of this sketch? (check the instructables page)
      - The angle doesn't change when I hit the "channel down/up" buttons
          - Are you sure that you have the correct IR code for each of your buttons?
          - Do you have the latest version of this sketch? (check the instructables page)
          - Are you sure that your servo is working and wired up correctly?
      - The fan doesn't turn on
          - Have you tested it with another power source?
*/
