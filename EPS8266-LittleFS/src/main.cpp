#include <Arduino.h>
#include "LittleFS.h"
 
void setup() {
  Serial.begin(9600);
  if(!LittleFS.begin()){
    Serial.println("LITTLEFS Mount Failed");
    return;
  }
  File file = LittleFS.open("/index.html", "r");
  if(!file){
     Serial.println("- failed to open file for reading");
    return;
  }
 Serial.println("- read from file:");
  while(file.available()){
    Serial.write(file.read());
  }
  file.close();
}
 
void loop() {
}