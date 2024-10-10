from adafruit_servokit import ServoKit

class ServoControl:
    def __init__(self):
        self.kit = ServoKit(channels=16)

    def set_servo_angle(self, channel, angle):
        self.kit.servo[channel].angle = angle

if __name__ == "__main__":
    servo_control = ServoControl()
    ports = [13, 12, 9, 8, 5, 4, 1, 0]
    for pin in ports:
        servo_control.set_servo_angle(pin, 0)

    # Can insert more values for smoother standing up of the servo,
    # although logically speaking, servos should have same speed, and
    # code should have minimal delay, so this operation shoudl work
    # unless its too fast
    
    for pin in ports:
        servo_control.set_servo_angle(pin, 45)
    

