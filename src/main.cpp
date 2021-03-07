#include <ArduinoRS485.h> // ArduinoModbus depends on the ArduinoRS485 library
#include <ArduinoModbus.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>

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

int relays[16] = {
    0x0001,
    0x0002,
    0x0003,
    0x0004,
    0x0005,
    0x0006,
    0x0007,
    0x0008,
    0x0009,
    0x0010,
    0x0A,
    0x0B,
    0x0C,
    0x0D,
    0x0E,
    0x0F};

void setup()
{
    Serial.begin(9600);
    while (!Serial)
        ;

    Serial.println("Modbus RTU Client Kitchen Sink");

    // start the Modbus RTU client
    if (!ModbusRTUClient.begin(9600))
    {
        Serial.println("Failed to start Modbus RTU Client!");
        while (1)
            ;
    }
    pinMode(PIN_BUTTON, INPUT);
    pinMode(PIN_RELAY, OUTPUT);
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
        for (byte i = 0; i < 16; ++i)
        {
            ModbusRTUClient.holdingRegisterWrite(0x01, relays[i], 0x0100);
        }

        digitalWrite(PIN_RELAY, LOW);
        setOledButtonHigh();
        break;
    case LOW:
        for (byte i = 0; i < 16; ++i)
        {
            ModbusRTUClient.holdingRegisterWrite(0x01, relays[i], 0x0200);
        }
        digitalWrite(PIN_RELAY, HIGH);
        setOledButtonLow();
        break;
    }
    // R421A08 8 przekaźników po Modbus RS485

    // Description of the board control:
    // The designation 0x0 means that the entry is hex in brackets gives the values ​​dec

    // no. you select devices (slave address) with DIP Switch (switches on the board) and set 2

    // register number - each relay is another register
    // 0x0001 (1)
    // 0x0002 (2)
    // 0x0003 (etc.)
    // 0x0004
    // 0x0005
    // 0x0006
    // 0x0007
    // 0x0008 (8)
    // commands
    // 0x0100 (256) ON
    // 0x0200 (512) OFF
    // 0x0300 (768) Change state if ON it changes to OFF lob if currently OFF it changes to ON
    // 0x0400 (1024) extinguishes all other lights selected
    // 0x0500 (1280) extinguishes all and turns the selected one on for 1 sec
    // 0x0601 - 0x06FF (1537-1791) is a time switch on from 1-255 sec
    // ModbusRTUClient.holdingRegisterWrite(0x01, 0x0001, 0x0100);
    // delay(100);
    // ModbusRTUClient.holdingRegisterWrite(0x01, 0x0001, 0x0200);
    // delay(100);
    // ModbusRTUClient.holdingRegisterWrite(0x01, 0x0002, 0x0100);
    // delay(100);
    // ModbusRTUClient.holdingRegisterWrite(0x01, 0x0002, 0x0200);
    // delay(100);
    // ModbusRTUClient.holdingRegisterWrite(0x01, 0x0003, 0x0100);
    // delay(100);
    // ModbusRTUClient.holdingRegisterWrite(0x01, 0x0003, 0x0200);
    // delay(100);
    // ModbusRTUClient.holdingRegisterWrite(0x01, 0x0004, 0x0100);
    // delay(100);
    // ModbusRTUClient.holdingRegisterWrite(0x01, 0x0004, 0x0200);
    // delay(100);
    // ModbusRTUClient.holdingRegisterWrite(0x01, 0x0005, 0x0100);
    // delay(100);
    // ModbusRTUClient.holdingRegisterWrite(0x01, 0x0005, 0x0200);
    // delay(100);
    // ModbusRTUClient.holdingRegisterWrite(0x01, 0x0006, 0x0100);
    // delay(100);
    // ModbusRTUClient.holdingRegisterWrite(0x01, 0x0006, 0x0200);
    // delay(100);
    // ModbusRTUClient.holdingRegisterWrite(0x01, 0x0007, 0x0100);
    // delay(100);
    // ModbusRTUClient.holdingRegisterWrite(0x01, 0x0007, 0x0200);
    // delay(100);
    // ModbusRTUClient.holdingRegisterWrite(0x01, 0x0008, 0x0100);
    // delay(100);
    // ModbusRTUClient.holdingRegisterWrite(0x01, 0x0008, 0x0200);
    // delay(100);
    // ModbusRTUClient.holdingRegisterWrite(0x01, 0x0009, 0x0100);
    // delay(100);
    // ModbusRTUClient.holdingRegisterWrite(0x01, 0x0009, 0x0200);
    // delay(100);
    // ModbusRTUClient.holdingRegisterWrite(0x01, 0x0010, 0x0100);
    // delay(100);
    // ModbusRTUClient.holdingRegisterWrite(0x01, 0x0010, 0x0200);
    // delay(100);
    // ModbusRTUClient.holdingRegisterWrite(0x01, 0x00101, 0x0100);
    // delay(100);
    // ModbusRTUClient.holdingRegisterWrite(0x01, 0x00101, 0x0200);
    // delay(100);
}