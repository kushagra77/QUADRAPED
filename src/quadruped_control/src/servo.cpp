#include "Servo.h"
#include <pigpio.h>
#include <stdio.h>

#define ROTATE_0 700  // Rotate to 0° position
#define ROTATE_180 2300

Servo::Servo(uint8_t gp) {
	xGP = gp;

	if (gpioInitialise() < 0) {
		printf("pigpio initialization failed\n");
		return;
	}

	gpioSetMode(gp, PI_OUTPUT);
	gpioSetPWMrange(gp, 20000);
	gpioPWM(gp, ROTATE_0);
}

void Servo::goDegree(double degree){
	if (degree > 180.0){
		return;
	}
	if (degree < 0){
		return;
	}

	int duty = (((double)(ROTATE_180 - ROTATE_0) / 180.0) * degree) + ROTATE_0;

	// printf("PWM for %f deg is %d duty\n", degree, duty);

	gpioPWM(xGP, duty);
}
