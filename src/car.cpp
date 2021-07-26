#include <memory>
#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/pose.hpp"
#include "geometry_msgs/msg/pose_array.hpp"
#include "visualization_msgs/msg/marker.hpp"
#include "visualization_msgs/msg/marker_array.hpp"

using namespace std;
using namespace chrono_literals;
using placeholders::_1;

class CarNode : public rclcpp::Node
{
public:
    CarNode(): Node("car")
    {
        marker_publisher = this->create_publisher<visualization_msgs::msg::MarkerArray>("car", 10);
        poses_subscriber = this->create_subscription<geometry_msgs::msg::PoseArray>("sine_path" , 10, bind(&CarNode::topic_callback, this, _1));

        visualization_msgs::msg::MarkerArray markerArray;
        visualization_msgs::msg::Marker marker;
        geometry_msgs::msg::Pose pose;

        marker.header.frame_id = "map";
        marker.ns = "my_namespace";
        marker.id = 0;
        marker.type = visualization_msgs::msg::Marker::CUBE;
        marker.action = visualization_msgs::msg::Marker::ADD;
        pose.position.x = 0.0;
        pose.position.y = 2.0;
        pose.position.z = 0.0;
        marker.pose.orientation.x = 0.0;
        marker.pose.orientation.y = 0.0;
        marker.pose.orientation.z = 0.0;
        marker.pose.orientation.w = 1.0;
        marker.scale.x = 1.5;
        marker.scale.y = 4;
        marker.scale.z = 0;
        marker.color.a = 1.0;
        marker.color.r = 0.0;
        marker.color.g = 0.0;
        marker.color.b = 1.0;

        marker.pose = pose;
        markerArray.markers.push_back(marker);
        marker_publisher->publish(markerArray);



    }


private:
    void topic_callback(const geometry_msgs::msg::PoseArray::SharedPtr msg) const
    {

    }

    rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr marker_publisher;
    rclcpp::Subscription<geometry_msgs::msg::PoseArray>::SharedPtr poses_subscriber;

};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = make_shared<CarNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}