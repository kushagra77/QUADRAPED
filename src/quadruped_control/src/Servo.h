#ifndef SERVO_H
#define SERVO_H

#define SERVO_SRC_SERVO_H_

#include <pigpio.h>  // Include pigpio library for Raspberry Pi

class Servo {
public:
    Servo();
    Servo(uint8_t gp);

    /**
     * move to angle: 0 to 180.
     * @param degree
     */
    void goDegree(double degree);

    bool operator==(const Servo& other) const {
        return this->xGP == other.xGP; // Compare based on GPIO pin
    }

private:
    uint8_t xGP = 0;
};

#endif