SYSTEM_MODE(MANUAL)
SYSTEM_THREAD(ENABLED)

#include "oled-wing-adafruit.h"
#include "LIS3DH.h"

OledWingAdafruit display;
LIS3DHSPI accel(SPI, D3, WKP);
const unsigned long PRINT_SAMPLE_PERIOD = 100;
unsigned long lastPrintSample = 0;

void setup()
{
	display.setup();
	display.clearDisplay();
	display.setCursor(0, 0);
	display.setTextSize(1);
	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.println("DISPLAY CONNECTED");
	display.display();
	delay(2000);
	LIS3DHConfig config;
	config.setAccelMode(LIS3DH::RATE_100_HZ);
	accel.setup(config);
}

void loop()
{
	display.loop();
	if (millis() - lastPrintSample >= PRINT_SAMPLE_PERIOD)
	{
		lastPrintSample = millis();

		LIS3DHSample sample;
		if (accel.getSample(sample))
		{
			display.clearDisplay();
			display.setCursor(0, 0);
			display.setTextSize(1);
			display.print(sample.x);
			display.println(" - X");
			display.print(sample.y);
			display.println(" - Y");
			display.print(sample.z);
			display.println(" - Z");
			display.display();
			delay(200);
		}
		else
		{
			display.clearDisplay();
			display.setCursor(0, 0);
			display.setTextSize(1);
			display.println("no sample");
			display.display();
		}
	}
}