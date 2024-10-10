#include "rclcpp/rclcpp.hpp"
#include <vector>
#include <cmath>
#include <array>
#include <iostream>
#include "quadruped_interfaces/msg/pos.hpp"
#include "std_msgs/msg/int32_multi_array.hpp"

class MotorConfig : public rclcpp::Node
{
public:
    MotorConfig()
    : Node("motor_config"), pwm_max(2400), pwm_min(370), leg_num(0)
    {
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(1000),
            std::bind(&MotorConfig::crawl_gait, this)
        );

        front_left_upper = 9;
        front_left_lower = 8;
        front_right_upper = 13;
        front_right_lower = 12;
        back_left_upper = 5;
        back_left_lower = 4;
        back_right_upper = 1;
        back_right_lower = 0;

        pins = {{{13, 9, 1, 5}, {12, 8, 0, 4}}};

        // front_left_upper_servo = Servo(front_left_upper);
        // front_left_lower_servo = Servo(front_left_lower);
        // front_right_upper_servo = Servo(front_right_upper);
        // front_right_lower_servo = Servo(front_right_lower);
        // back_left_upper_servo = Servo(back_left_upper);
        // back_left_lower_servo = Servo(back_left_lower);
        // back_right_upper_servo = Servo(back_right_upper);
        // back_right_lower_servo = Servo(back_right_lower);

        // right_leg_servo_list = {front_right_upper_servo, front_right_lower_servo, back_right_upper_servo, back_right_lower_servo};
        // left_leg_servos_list = {front_left_upper_servo, front_left_lower_servo, back_left_upper_servo, back_left_lower_servo};
        left_leg_servos_list = {9, 8, 5, 4};

        // upper_servos = {front_left_upper_servo, front_right_upper_servo, back_left_upper_servo, back_right_upper_servo};
        // lower_servos = {front_left_lower_servo, front_right_lower_servo, back_left_lower_servo, back_right_lower_servo};

        position_publisher_ = this->create_publisher<quadruped_interfaces::msg::Pos>("destination", 10);
        servo_publisher_ = this->create_publisher<std_msgs::msg::Int32MultiArray>("servo_control_topic", 10);

        subscription_ = this->create_subscription<quadruped_interfaces::msg::Pos>(
            "joint_angles", 10, std::bind(&MotorConfig::gait_callback, this, std::placeholders::_1)
        );
    }

    void crawl_gait()
    {
        std::vector<std::vector<std::pair<double, double>>> relative_positions = {
            {{10.29, 22.68}, {10.29, 22.68}, {10.29, 22.68}, {10.29, 22.68}},  // Position 1
            {{7.39, 23.86}, {7.39, 23.86}, {7.39, 23.86}, {7.39, 23.86}},    // Position 2
            {{4.34, 24.62}, {4.34, 24.62}, {4.34, 24.62}, {4.34, 24.62}},    // Position 3
            {{1.22, 24.95}, {1.22, 24.95}, {1.22, 24.95}, {1.22, 24.95}},    // Position 4
            {{-1.91, 24.83}, {-1.91, 24.83}, {-1.91, 24.83}, {-1.91, 24.83}}, // Position 5
            {{-4.98, 24.28}, {-4.98, 24.28}, {-4.98, 24.28}, {-4.98, 24.28}}, // Position 6
            {{-7.93, 23.31}, {-7.93, 23.31}, {-7.93, 23.31}, {-7.93, 23.31}}, // Position 7
            {{-10.69, 21.95}, {-10.69, 21.95}, {-10.69, 21.95}, {-10.69, 21.95}}
        };

        for (const auto& gait_phase : relative_positions)
        {
            for (const auto& position : gait_phase) {
                quadruped_interfaces::msg::Pos msg;
                msg.x = position.first;
                msg.z = position.second;
                position_publisher_->publish(msg);
            }
            rclcpp::sleep_for(std::chrono::milliseconds(500));
        }
    }

private:
    // void set_servo_angle(Servo servo, float angle)
    // {
    //     if (angle == -1)
    //     {
    //         servo.goDegree(0);
    //     }
    //     else
    //     {
    //         servo.goDegree(angle);
    //     }
    // }

    // void move_abs_angle(Servo servo, float angle)
    // {
    //     if (std::find(left_leg_servos_list.begin(), left_leg_servos_list.end(), servo) != left_leg_servos_list.end())
    //     {
    //         set_servo_angle(servo, -1 * angle);
    //     }
    //     else
    //     {
    //         set_servo_angle(servo, angle);
    //     }
    // }

    void publish_servo_data(int pin, float angle)
    {
        auto msg = std_msgs::msg::Int32MultiArray();
        msg.data.push_back(pin);
        msg.data.push_back(static_cast<int>(angle));
        servo_publisher_->publish(msg);
    }

    void gait_callback(const quadruped_interfaces::msg::Pos::SharedPtr msg)
    {
        double angle1 = msg->x;
        double angle2 = msg->z;

        // Set servo angles and publish to the servo control topic
        // move_abs_angle(upper_servos[leg_num / 2], angle1);
        // move_abs_angle(lower_servos[leg_num / 2], angle2);

        // Publish the pin and angle for each servo
        publish_servo_data(pins[0][leg_num], angle1);  // Upper servo
        publish_servo_data(pins[1][leg_num], angle2);  // Lower servo

        leg_num++;
        if (leg_num == 4)
        {
            leg_num = 0;
        }
    }

    int pwm_max;
    int pwm_min;

    int front_left_upper, front_left_lower;
    int front_right_upper, front_right_lower;
    int back_left_upper, back_left_lower;
    int back_right_upper, back_right_lower;

    // Servo front_left_upper_servo, front_left_lower_servo;
    // Servo front_right_upper_servo, front_right_lower_servo;
    // Servo back_left_upper_servo, back_left_lower_servo;
    // Servo back_right_upper_servo, back_right_lower_servo;

    std::array<std::array<int, 4>, 2> pins;

    // std::vector<Servo> right_leg_servo_list;
    // std::vector<Servo> left_leg_servos_list;
    std::vector<int> left_leg_servos_list;
    // std::vector<Servo> upper_servos;
    // std::vector<Servo> lower_servos;

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<quadruped_interfaces::msg::Pos>::SharedPtr position_publisher_;
    rclcpp::Publisher<std_msgs::msg::Int32MultiArray>::SharedPtr servo_publisher_;
    rclcpp::Subscription<quadruped_interfaces::msg::Pos>::SharedPtr subscription_;

    int leg_num;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto motor_config = std::make_shared<MotorConfig>();
    motor_config->crawl_gait();
    rclcpp::spin(motor_config);
    rclcpp::shutdown();

    return 0;
}
