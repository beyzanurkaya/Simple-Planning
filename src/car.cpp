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
int x = 0;

class CarNode : public rclcpp::Node
        {
        public:
            CarNode(): Node("car")
            {
                marker_publisher = this->create_publisher<visualization_msgs::msg::Marker>("car", 10);
                poses_subscriber = this->create_subscription<geometry_msgs::msg::PoseArray>("sine_path" , 10, bind(&CarNode::topic_callback, this, _1));

            }


        private:


            void topic_callback(const geometry_msgs::msg::PoseArray::SharedPtr msg) const
            {
                visualization_msgs::msg::Marker markerD;
                markerD.header.frame_id = "map";
                markerD.action = visualization_msgs::msg::Marker::DELETEALL;
                int i = 0;
                auto message = visualization_msgs::msg::Marker();
                visualization_msgs::msg::Marker marker;
                marker.header.frame_id = "map";
                marker.ns = "my_namespace";
                marker.id = 0;
                marker.type = visualization_msgs::msg::Marker::CUBE;
                marker.action = visualization_msgs::msg::Marker::ADD;

                marker.pose.orientation.x = 0.0;
                marker.pose.orientation.y = 0.0;
                marker.pose.orientation.z = 0.0;
                marker.pose.orientation.w = 1.0;

                marker.scale.x = 4.0;
                marker.scale.y = 1.5;
                marker.scale.z = 1.0;

                marker.color.r = 0.0f;
                marker.color.g = 0.0f;
                marker.color.b = 1.0f;
                marker.color.a = 1.0;
                do {
                    geometry_msgs::msg::Pose p = msg->poses.at(i);
                    marker.pose = p;
                    i++;
                    message = marker;
                    marker_publisher->publish(message);
                    rclcpp::sleep_for(1s);
                    marker_publisher->publish(markerD);
                }while(i < 360);

            }

            rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr marker_publisher;
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