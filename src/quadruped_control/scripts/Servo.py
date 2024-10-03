import rclpy
from rclpy.node import Node
from adafruit_servokit import ServoKit

# Define constants
ROTATE_0 = 700     # 0° position in microseconds
ROTATE_180 = 2300  # 180° position in microseconds

class Servo():
    def __init__(self, servo_channel=0):
        super().__init__('servo_controller_node')
        
        # Initialize the ServoKit instance for 16-channel PCA9685
        self.kit = ServoKit(channels=16)

        # Set the servo channel (e.g., 0)
        self.servo_channel = servo_channel

        # Initialize servo to 0 degrees
        self.go_degree(0)

    def go_degree(self, degree):
        if degree > 180.0 or degree < 0:
            self.get_logger().warn(f"Degree {degree} out of range, must be between 0 and 180.")
            return

        # Calculate the duty cycle equivalent for the given degree
        duty_cycle = (((ROTATE_180 - ROTATE_0) / 180.0) * degree) + ROTATE_0

        # Convert microseconds to a percentage for the PCA9685
        pulse_width_percentage = duty_cycle / 20000.0

        # Set the angle using the Adafruit PCA9685 library
        self.kit.servo[self.servo_channel].fraction = pulse_width_percentage
        self.get_logger().info(f"Set servo to {degree} degrees")

def main(args=None):
    rclpy.init(args=args)
    node = Servo()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
