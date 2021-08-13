#include <memory>
#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/pose.hpp"
#include "geometry_msgs/msg/pose_array.hpp"

using namespace std;
using namespace chrono_literals;

class SinePath : public rclcpp::Node
{
public:

    SinePath() : Node("sinePath"){

        poses_publisher = this->create_publisher<geometry_msgs::msg::PoseArray>("sine_path", 10);
        timer_ = this->create_wall_timer(500ms, std::bind(&SinePath::timer_callback, this));
    }

private:
    void timer_callback()
    {

        auto message = geometry_msgs::msg::PoseArray();
        geometry_msgs::msg::PoseArray poseArray;
        geometry_msgs::msg::Pose p;
        poseArray.header.frame_id = "map";
        poseArray.header.stamp = this->now();

        for(int i=0;i<=360;i++){
            p.position.x  = static_cast<float>(i);
            p.position.y = 10*sin(static_cast<float>(i) * M_PI / 5);
            p.position.z = 0;
            p.orientation.x  = 1;
            p.orientation.y =  1;
            p.orientation.z = 0;
            p.orientation.w = 1;
            poseArray.poses.push_back(p);
        }
        message = poseArray;
        poses_publisher->publish(message);
    }

    rclcpp::Publisher<geometry_msgs::msg::PoseArray>::SharedPtr poses_publisher;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SinePath>());
    rclcpp::shutdown();
    return 0;
}