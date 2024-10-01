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

private:
    uint8_t xGP = 0;
};

