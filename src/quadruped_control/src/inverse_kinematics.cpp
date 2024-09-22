#include "rclcpp/rclcpp.hpp"
#include "quadruped_interfaces/msg/pos.hpp"
#include <cmath>

// Both a publisher and subscriber, subscribes to a gait, publishes an angle which is subscribed by the servo
class InverseKinematics : public rclcpp::Node
{
public:
    InverseKinematics()
    : Node("inverse_kinematics")
    {
        publisher_ = this->create_publisher<quadruped_interfaces::msg::Pos>("joint_angles", 10);

        subscription_ = this->create_subscription<quadruped_interfaces::msg::Pos>(
            "destination", 10, std::bind(&InverseKinematics::topic_callback, this, std::placeholders::_1));

        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(500),
            std::bind(&InverseKinematics::timer_callback, this));
    }

    // Probably better for the position struct to go in the Servo's node, with the inverse kinematics node referencing it
    // This struct also needs a custom message interface or srv file if made a service instead of publisher/subscriber.
    struct pos
    {
        double x = 0;
        double z = 0;

        pos(double x, double z) : x(x), z(z) {}

        pos& operator=(const pos& a) {
            x = a.x;
            z = a.z;
            return *this;
        }

        pos operator+(const pos& a) const {
            return pos(a.x+x, a.z+z);
        }

        pos operator-(const pos& a) const {
            return pos(x-a.x, z-a.z);
        }

        bool operator==(const pos& a) const {
            return (x == a.x && z == a.z);
        }
    };

private:
    void timer_callback()
    {
        if (new_position_received_) {
            auto message = quadruped_interfaces::msg::Pos();
            message.data = new_coords;
            publisher_->publish(message);
            new_position_received_ = false;
        }
    }

    void topic_callback(const quadruped_interfaces::msg::Pos::SharedPtr msg) const
    {
        dest_ = pos(msg->x, msg->z);  // Receive destination pos (x, z)
        new_coords = inverseKinematics(dest_);
        new_position_received_ = true;
    }

    // Need a method which computes the relative position of each servo/leg?

    pos inverseKinematics(pos destination) {
        static constexpr double link1 = 6.4; // Need to double check with current model what the leg lengths actually are
        static constexpr double link2 = 5.9;

        double x = dest.x;
        double z = dest.z;
        double r = sqrt(x*x + z*z);
        double theta1, theta2, beta1, beta2;

        // Calculates the angle in at the joint, or in between 2 leg components
        double temp1 = (link1*link1 + link2*link2 - r*r)/(2*link1*link2);
        // If angle exceeds 1, then return to original position
        // Isn't range of motion +- 55 degrees though?
        // As this is a check, can replace the constant.
        if (abs(temp1) > 1) {
            return pos(0, 0);
        }

        beta1 = acos(temp1);

        // Not 100% sure what this one calculates, but looks like not super necessary
        double temp2 = link2*sin(beta1)/r;

        if (abs(temp2) > 1) {
            return pos(0, 0);
        }

        beta2 = asin(temp2);

        // if (x == 0) {
        //     // If thigh is vertical, and knee is (probably not going to be flipped over that much)
        //     if (z > 0) {
        //         theta1 = 90;
        //     } else if (z < 0) {
        //         theta1 = -90;
        //     } else {
        //         theta1 = 0;
        //     }
        // } else {

        theta2 = acos((x * x + z * z - link1 * link1 - link2 * link2) / (2 * link1 * link2));

        theta1 = (180/PI)*(atan(z/x) - atan((link2*sin(theta2))/(link1 + link2*cos(theta2)));

        theta2 *= (180/PI);

        // Other version for angle calculation based on video by Engineer M
        // double x = dest.x;
        // double z = dest.z;
        // double r = sqrt(x*x + z*z);
        // double theta1, theta2, beta1, beta2, beta3;

        // beta1 = atan(z/x);
        // beta2 = acos((link1*link1 + r*r - link2*link2)/(2*link1*r));
        // beta3 = acos((link1*link1 + link2*link2 - r*r)/(2*link1*link2));
        // theta1 = (180/PI) * (beta1 - beta2);
        // theta2 = (180/PI) * (PI - beta3);
        

        // if (r == abs(z)) {
        //     // If horizonatal component is 0, so the thigh is horizontal
        //     theta2 = (180/PI)*(PI/2 + eha);
        // } else {
        //     theta2 = (180/PI) * (atan(z/(sqrt(x*x + y*y))) + eha);
        // }

        return pos(theta1, theta2)
    }

    rclcpp::Subscription<quadruped_interfaces::msg::Pos>::SharedPtr subscription_;
    rclcpp::Publisher<quadruped_interfaces::msg::Pos>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;

    struct pos dest_, new_coords;
    bool new_position_received_ = false;
};    

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<InverseKinematics>());
    rclcpp::shutdown();
    return 0;
}
