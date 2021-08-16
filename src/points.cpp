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

class PointsNode : public rclcpp::Node
{
public:
    PointsNode(): Node("points")
    {
        markers_publisher = this->create_publisher<visualization_msgs::msg::MarkerArray>("points", 10);
        poses_subscriber = this->create_subscription<geometry_msgs::msg::PoseArray>("sine_path" , 10, bind(&PointsNode::topic_callback, this, _1));
    }


private:
    void topic_callback(const geometry_msgs::msg::PoseArray::SharedPtr msg) const
    {
        auto message = visualization_msgs::msg::MarkerArray();
        visualization_msgs::msg::MarkerArray markerArray;
        visualization_msgs::msg::Marker marker;
        
        for(int i=0;i<=360;i++){

            marker.header.frame_id = "map";
            marker.ns = "my_namespace";
            marker.id = i;
            marker.type = visualization_msgs::msg::Marker::SPHERE;
            marker.action = visualization_msgs::msg::Marker::ADD;
            marker.pose.orientation.x = 1.0;
            marker.pose.orientation.y = 1.0;
            marker.pose.orientation.z = 0.0;
            marker.pose.orientation.w = 1.0;
            marker.scale.x = 1;
            marker.scale.y = 1;
            marker.scale.z = 1;
            marker.color.a = 1.0;
            marker.color.r = 1.0;
            marker.color.g = 0.0;
            marker.color.b = 0.0;


            geometry_msgs::msg::Pose pose = msg->poses.at(i);
            marker.pose.position.x = pose.position.x;
            pose.position.y = pose.position.y;
            pose.position.z = pose.position.z;
            marker.pose = pose;
            markerArray.markers.push_back(marker);
        }
        message = markerArray;
        markers_publisher->publish(message);

    }

    rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr markers_publisher;
    rclcpp::Subscription<geometry_msgs::msg::PoseArray>::SharedPtr poses_subscriber;

};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = make_shared<PointsNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}