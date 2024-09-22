#include "rclcpp/rclcpp.hpp"
#include <vector>
#include <cmath>
#include <array>
#include <iostream>
#include "quadruped_interfaces/msg/pos.hpp"
#include "Servo.h"
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

        right_leg_servo_list = {front_right_upper, front_right_lower, back_right_upper, back_right_lower};
        left_leg_servos_list = {front_left_upper, front_left_lower, back_left_upper, back_left_lower};

        front_left_upper_servo = new Servo(front_left_upper);
        front_left_lower_servo = new Servo(front_left_lower);

        front_right_upper_servo = new Servo(front_right_upper);
        front_right_lower_servo = new Servo(front_right_lower);

        back_left_upper_servo = new Servo(back_left_upper);
        back_left_lower_servo = new Servo(back_left_lower);

        back_right_upper_servo = new Servo(back_right_upper);
        back_right_lower_servo = new Servo(back_right_lower);
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

    void move_abs_angle(Servo servo, int servo_number, float angle)
    {
        // Corrects left leg movement to match the right leg
        if (std::find(left_leg_servos_list.begin(), left_leg_servos_list.end(), servo_number) != left_leg_servos_list.end())
        {
            set_servo_angle(servo, 180 - angle);
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
        std::vector<std::pair<float, float>> relative_positions = {
            {0.1f, 0.2f}, {0.2f, 0.15f}, {0.3f, 0.1f}, {0.4f, 0.05f}
        };

        for (const auto& position : relative_positions)
        {
            auto [x, z] = position;
            std::pair<float, float> angles1 = ik->calculate_angles(x, z);
            std::pair<float, float> angles2 = ik->calculate_angles(x, z);
            std::pair<float, float> angles3 = ik->calculate_angles(x, z);
            std::pair<float, float> angles4 = ik->calculate_angles(x, z);

            move_abs_angle(front_left_upper_servo, front_left_upper, angles1.first);
            move_abs_angle(front_left_lower_servo, front_left_lower, angles1.second);

            move_abs_angle(front_right_upper_servo, front_right_upper, angles2.first);
            move_abs_angle(front_right_lower_servo, front_right_lower, angles2.second);

            move_abs_angle(back_left_upper_servo, back_left_upper, angles3.first);
            move_abs_angle(back_left_lower_servo, back_left_lower, angles3.second);

            move_abs_angle(back_right_upper_servo, back_right_upper, angles4.first);
            move_abs_angle(back_right_lower_servo, back_right_upper, angles4.second);

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

    std::vector<int> right_leg_servo_list;
    std::vector<int> left_leg_servos_list;

    std::vector<std::vector<std::pair<float, float>>> group_positions_;
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
