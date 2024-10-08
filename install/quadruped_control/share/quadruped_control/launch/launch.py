from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='quadruped_control',
            # namespace='quadruped',
            executable='motor_config',
            name='servos'
        ),
        Node(
            package='quadruped_control',
            # namespace='quadruped',
            executable='inverse_kinematics',
            name='inverse_kinematics'
        )
    ])