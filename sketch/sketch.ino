#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET     -1 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define ANALOG_PIN_0 32


const int outputPins[8] = {26, 27, 14, 12, 13, 15, 2, 33};

unsigned long lastPatternUpdate = 0;
const int patternSpeed = 150;
int currentStep = 0;
int direction = 1; 

unsigned long lastOledUpdate = 0;
const int oledSpeed = 100;

void setup() {
  Serial.begin(9600);
  

  for (int i = 0; i < 8; i++) {
    pinMode(outputPins[i], OUTPUT);
    digitalWrite(outputPins[i], LOW);
  }

  Wire.begin(16, 17);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); 
  }
  
  display.display();
  delay(1000); 
}

void loop() {
  unsigned long currentMillis = millis();


  if (currentMillis - lastPatternUpdate >= patternSpeed) {
    lastPatternUpdate = currentMillis;

    for (int i = 0; i < 8; i++) {
      digitalWrite(outputPins[i], LOW);
    }

    digitalWrite(outputPins[currentStep], HIGH);

    currentStep = currentStep + direction;

    if (currentStep == 7 || currentStep == 0) {
      direction = -direction; 
    }
  }

 
  if (currentMillis - lastOledUpdate >= oledSpeed) {
    lastOledUpdate = currentMillis;

    int adcValue = analogRead(ANALOG_PIN_0);

    display.clearDisplay();
    display.setTextSize(2);      
    display.setTextColor(WHITE); 
    
    display.setCursor(0, 10);
    display.print("ADC Val:");
    
    display.setCursor(0, 35);
    display.print(adcValue);

    display.display();
  }
}