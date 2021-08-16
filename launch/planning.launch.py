from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package="rviz2",
            executable="rviz2",
            name="rviz2"
        ),
        Node(
            package='motion_planning',
            executable='sine_path',
            output='screen'
        ),
        Node(
            package='motion_planning',
            executable='points',
            output='screen'
        ),
        Node(
            package='motion_planning',
            executable='car',
            output='screen'
        )
    ])




