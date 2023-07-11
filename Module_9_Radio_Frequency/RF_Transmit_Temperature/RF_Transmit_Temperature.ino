#include <TMP117.h> // Include Temperature Sensor Library dependency
#include <GLEE_Radio.h> // Include GLEE_Radio library dependency 

///////////////////////////////////////////////
String id = "44"; // CHANGE TO YOUR TEAM NUMBER
///////////////////////////////////////////////

// Initiate LunaSat Radio (SX1272 Transciever)
LunaRadio Rad;

// Instantiate TMP117 class with id of one and debugging set to true
TMP117 thermometer(1,true);

// Initialize buffer and string variables used in data conversion for transmission
char data_buffer[16]; // Character array (buffer) for string-numerical conversiona
String temperature_string; 
String full_message;

// Temperature Threshold Value
int temperature_threshold = 20; // User-defined threshold

// Delay between samples in ms
int sampleDelay = 1000; // User-defined sample period

// Dynamic Variables 
float temperatureF;
float temperatureC;   // Variable to store an observed temperature in Fahrenheit
float startTime;    // Variables for timing offset calculations
float endTime;

// Red LED Pin (for indicating transmission)
int LED = 4;

void setup(){
    Serial.begin(9600);

    // Initialize Transciever with following parameters
    // Argument 1: Set frequency to 915
    // Argument 2: Set output power to 17
    // Argument 3: Set Bandwidth to 250
    // Argument 4: Set spreading factor to 12
    // Argument 5: Set coding rate to 8
    Rad.initialize_radio(915.0, 7, 250.0, 12, 8);

    // Set LED (Red) pin as output
    pinMode(LED, OUTPUT);
}

void loop(){
    // Record start time for offsetting delay by run time
    startTime = millis();

    // Call the getTemperatureF() function of the TMP117 thermometer 
    temperatureF = thermometer.getTemperatureF();
    temperatureC = ((temperatureF - 32)*5)/9;
    // Output the temperature via seiral
    Serial.println(temperatureC);
    
    // Check if the temperature exceeds the threshold
    if(temperatureC > temperature_threshold){
        // If theshold exceeded, transmit temperature
        Serial.println("Threshold Exceeded, Transmitting Temperature...");
        
        // Convert int temperature to arduino String
        temperature_string = String(temperatureC);

        // Format full message with ID preamble
        full_message = String(id + " " + temperature_string);

        // Convert string to byte/char array stored in buffer
        full_message.toCharArray(data_buffer,10);

        // Transmit buffer containing temperature in the form of a byte array
        Rad.transmit_data(data_buffer);

        // Blink LED on transmission 
        digitalWrite(LED, HIGH);
        delay(500);
        digitalWrite(LED, LOW);
    }

    // Record the end time for delay offset
    endTime = millis();
    
    // Check if processing time between sample and possible transmission is less than sample delay
    if((endTime - startTime)< sampleDelay){
        delay(sampleDelay - (endTime - startTime));  
    } else { // If it is larger, delay by constant 1000ms (1s)
        delay(1000);
    }
}


float CtoF(float c){ // Function to convert from Celsius to Farenheit
  return c*(9.0f/5.0f)+32;
}