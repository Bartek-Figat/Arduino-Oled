#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// declare an SSD1306 display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int PIN_BUTTON = 12;
int PIN_RELAY = 11;

void setOledButtonHigh()
{
    oled.clearDisplay();
    oled.setCursor(20, 30);
    oled.setTextSize(1);
    oled.setTextColor(WHITE);
    oled.println("Arduino Project"); // text to display
    oled.display();
}

void setOledButtonLow()
{
    oled.clearDisplay();
    oled.setCursor(40, 30);
    oled.setTextSize(1);
    oled.setTextColor(WHITE);
    oled.println("for 2021"); // text to display
    oled.display();
}

void setup()

{
    pinMode(PIN_BUTTON, INPUT);
    pinMode(PIN_RELAY, OUTPUT);
    digitalWrite(PIN_BUTTON, LOW);
    if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C))
        // initialize OLED display with address 0x3C for 128x64
        if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C))
        {
            Serial.println(F("SSD1306 allocation failed"));
            while (true)
                ;
        }

    delay(2000);
}

void loop()
{
    switch (digitalRead(PIN_BUTTON))
    {
    case HIGH:
        digitalWrite(PIN_RELAY, HIGH);
        setOledButtonHigh();
        break;
    case LOW:
        digitalWrite(PIN_RELAY, LOW);
        setOledButtonLow();
        break;
    }
}