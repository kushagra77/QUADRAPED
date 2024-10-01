#include "rclcpp/rclcpp.hpp"
#include <vector>
#include <cmath>
#include <array>
#include <iostream>
#include "quadruped_interfaces/msg/pos.hpp"
#include "servo.h"
#include <pigpio.h>
// Then manually modify servo values using PWM.
// Use the changeDutyCycle feature
// To manually change motors in gait control, can probably use a list of values hardcoded in crawl_gait, then control the 
// timings of each position while calling inverse kinematics to get the two angle values, and reveres engineer to determin
// duty cycle?
// Z is up and X is forward position, so the two angles received are in order of upper motor, then lower motor.

class MotorConfig : public rclcpp::Node
{
public:
    MotorConfig()
    : Node("motor_config"), pwm_max(2400), pwm_min(370)
    {
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(1000),
            std::bind(&MotorConfig::crawl_gait, this)
        );

        // Initialize the PWM control ranges for each servo (to be used with a real PWM driver)
        // create();

        front_left_upper = 9;
        front_left_lower = 8;

        front_right_upper = 13;
        front_right_lower = 12;

        back_left_upper = 5;
        back_left_lower = 4;

        back_right_upper = 1;
        back_right_lower = 0;

        pins = {{13, 9, 1, 5},
                {12, 8, 0, 4}};

        // right_leg_servo_list = {front_right_upper, front_right_lower, back_right_upper, back_right_lower};
        // left_leg_servos_list = {front_left_upper, front_left_lower, back_left_upper, back_left_lower};

        front_left_upper_servo = new Servo(front_left_upper);
        front_left_lower_servo = new Servo(front_left_lower);

        front_right_upper_servo = new Servo(front_right_upper);
        front_right_lower_servo = new Servo(front_right_lower);

        back_left_upper_servo = new Servo(back_left_upper);
        back_left_lower_servo = new Servo(back_left_lower);

        back_right_upper_servo = new Servo(back_right_upper);
        back_right_lower_servo = new Servo(back_right_lower);

        right_leg_servo_list = {front_right_upper_servo, front_right_lower_servo, back_right_upper_servo, back_right_lower_servo};
        left_leg_servos_list = {front_left_upper_servo, front_left_lower_servo, back_left_upper_servo, back_left_lower_servo};

        upper_servos = {front_left_upper_servo, front_right_upper_servo, back_left_upper_servo, back_right_upper_servo};
        lower_servos = {front_left_lower_servo, front_right_lower_servo, back_left_lower_servo, back_right_lower_servo};

        position_publisher_ = this->create_publisher<quadruped_interfaces::msg::Pos>("destination", 10);
        
        subscription_angles_ = this->create_subscription<quadruped_interfaces::msg::Pos>(
            "joint_angles", 10, std::bind(&MotorConfig::angles_callback, this, std::placeholders::_1)
        );
        
    }

    // void create()
    // {
    //     for (int i = 0; i < 14; i++)
    //     {
    //         set_actuation_range(i, 180);
    //         set_pulse_width_range(i, pwm_min, pwm_max);
    //     }
    // }

    void calibrate_servo(int servo_number)
    {
        bool cal = false;
        while (!cal)
        {
            std::cout << "Input servo angle: ";
            float angle;
            std::cin >> angle;

            set_servo_angle(servo_number, angle);

            std::cout << "Is the servo fully vertical? y/n: ";
            char response;
            std::cin >> response;

            if (response == 'y')
            {
                cal = true;
                std::cout << "The calibration angle for servo " << servo_number << " is " << angle << std::endl;
            }
        }
    }

    void move_abs_angle(Servo servo, float angle)
    {
        // Corrects left leg movement to match the right leg
        // if (std::find(left_leg_servos_list.begin(), left_leg_servos_list.end(), servo_number) != left_leg_servos_list.end())
        if (std::find(left_leg_servos_list.begin(), left_leg_servos_list.end(), servo) != left_leg_servos_list.end())
        {
            // If directly downwards is 0, then we probably want to just use the negative rather than subtract from 180
            // Motors spin counter clockwise, meaning that motors on the right are in the default direction
            // and the motors on the left side need to be reversed
            set_servo_angle(servo, -1 * angle);
        }
        else
        {
            set_servo_angle(servo, angle);
        }
    }

    // void relax_all_motors()
    // {
    //     for (int i = 0; i < 14; i++)
    //     {
    //         try
    //         {
    //             set_servo_angle(i, -1);  // -1 means no signal, effectively "turning off" the servo
    //         }
    //         catch (const std::exception &e)
    //         {
    //             std::cerr << "Error occurred with servo " << i << ". Error message: " << e.what() << std::endl;
    //         }
    //     }
    // }

    void crawl_gait()
    {
        // Modify this to have 8 in each vector, 2 for each step.
        std::vector<std::vector<std::pair<double, double>>> relative_positions = {
            { {2.0, 1.0}, {1.5, 1.2}, {0.5, 0.8}, {-0.5, 1.5} },
            { {-2.0, 0.8}, {-1.5, 1.4}, {0.0, 1.0}, {0.5, 1.2} },
            { {1.8, 1.1}, {1.2, 1.6}, {0.3, 0.9}, {-0.3, 1.4} },
            { {-1.8, 0.9}, {-1.2, 1.3}, {0.2, 1.0}, {0.4, 1.5} },
            { {2.0, 1.0}, {1.5, 1.2}, {0.5, 0.7}, {-0.5, 1.4} },
            { {-2.0, 1.2}, {-1.5, 1.0}, {0.0, 1.1}, {0.6, 1.3} },
            { {1.9, 1.0}, {1.4, 1.5}, {0.4, 0.6}, {-0.4, 1.6} },
            { {-1.9, 0.7}, {-1.4, 1.2}, {0.1, 1.0}, {0.5, 1.4} } 
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
    int pwm_max;
    int pwm_min;

    int front_left_upper, front_left_lower;
    int front_right_upper, front_right_lower;
    int back_left_upper, back_left_lower;
    int back_right_upper, back_right_lower;

    std::array<std::array<int, 4>, 2> pins;

    std::vector<Servo> right_leg_servo_list;
    std::vector<Servo> left_leg_servos_list;

    std::vector<std::vector<std::pair<double, double>>> relative_positions;
    rclcpp::TimerBase::SharedPtr timer_;

    // void set_actuation_range(int servo, int range)
    // {
    // }

    // void set_pulse_width_range(int servo, int min, int max)
    // {
    // }

    void set_servo_angle(Servo servo, float angle)
    {
        // Placeholder for setting the servo angle (depends on hardware)
        if (angle == -1)
        {
            servo.goDegree(0);
        }
        else
        {
            servo.goDegree(angle);
        }
    }

    void gait_callback(const quadruped_interfaces::msg::Pos::SharedPtr msg) {
        // Process angles from inverse kinematics node each time the invk publisher updates
        double angle1 = msg->x;
        double angle2 = msg->z;

        // if (leg_num == 0) {
        //     move_abs_angle(front_left_upper_servo, front_left_upper, angle1);
        //     move_abs_angle(front_left_lower_servo, front_left_lower, angle2);
        // } else if (leg_num == 1) {
        //     move_abs_angle(front_right_upper_servo, front_right_upper, angle1);
        //     move_abs_angle(front_right_lower_servo, front_right_lower, angle2);
        // } else if (leg_num == 2) {
        //     move_abs_angle(back_left_upper_servo, back_left_upper, angle1);
        //     move_abs_angle(back_left_lower_servo, back_left_lower, angle2);
        // } else if (leg_num == 3) {
        //     move_abs_angle(back_right_upper_servo, back_right_upper, angle1);
        //     move_abs_angle(back_right_lower_servo, back_right_upper, angle2);
        // }

        move_abs_angle(upper_servos[leg_num/2], angle1);
        move_abs_angle(lower_servos[leg_num/2], angle2);

        leg_num++;
        if (leg_num == 8) {
            leg_num = 0;
        }
    }

    rclcpp::Publisher<quadruped_interfaces::msg::Pos>::SharedPtr position_publisher_;
    rclcpp::Subscription<quadruped_interfaces::msg::Pos>::SharedPtr subscription_;

    int leg_num = 0;
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
