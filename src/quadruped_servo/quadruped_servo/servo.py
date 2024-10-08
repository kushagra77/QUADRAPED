import rclpy
from rclpy.node import Node
from std_msgs.msg import Int32MultiArray
from adafruit_servokit import ServoKit

class ServoControlNode(Node):
    def __init__(self):
        super().__init__('servo_control_node')

        # Create the ServoKit object
        self.kit = ServoKit(channels=16)  # Assuming you're using a 16-channel ServoKit board
    
        # Subscriber to take input in the form of [channel, angle]
        self.subscription = self.create_subscription(
            Int32MultiArray, 
            'servo_control_topic', 
            self.servo_callback, 
            10)

        self.get_logger().info("Servo control node has started")

    def servo_callback(self, msg):
        # Expecting an Int32MultiArray message with two elements: [channel, angle]
        if len(msg.data) != 2:
            self.get_logger().warn("Received incorrect message format. Expected [channel, angle]")
            return

        channel = msg.data[0]
        angle = msg.data[1]

        # Validating the input values
        if channel < 0 or channel >= 16:
            self.get_logger().warn("Channel must be between 0 and 15")
            return

        if angle < 0 or angle > 180:
            self.get_logger().warn("Angle must be between 0 and 180")
            return

        # Set the servo to the desired angle on the specified channel
        self.kit.servo[channel].angle = angle
        self.get_logger().info(f"Moved servo on channel {channel} to angle {angle}")

def main(args=None):
    rclpy.init(args=args)
    node = ServoControlNode()

    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
