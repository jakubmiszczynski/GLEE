#include "CAP.h"

CAP cap(2,1);

void setup() {
	Serial.begin(9600);
	cap.begin();
}

void loop(){
	int rawData = cap.getRawData(); 
	Serial.println(rawData);
	delay(100);
};
