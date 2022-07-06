#include "oled-wing-adafruit.h"
#include "LIS3DH.h"
SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(MANUAL);
OledWingAdafruit display;

const unsigned long PRINT_SAMPLE_PERIOD = 100;

LIS3DHSPI accel(SPI, A2);

void setup()
{
	Serial.begin(9600);

	display.setup();
    display.clearDisplay();

	LIS3DHConfig config;
	config.setAccelMode(LIS3DH::RATE_100_HZ);
}

void loop()
{
	display.loop();
	LIS3DHSample sample;

	if (accel.getSample(sample))
	{

		display.clearDisplay();
		display.setTextSize(1);
		display.setTextColor(WHITE);
		display.setCursor(0, 0);
		display.printlnf("%d,%d,%d", sample.x, sample.y, sample.z);
		display.display();
		delay(200);
	}
}
