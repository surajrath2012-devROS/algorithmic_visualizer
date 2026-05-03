#include <memory>
#include <string>
#include <vector>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "visualization_msgs/msg/marker.hpp"
#include "visualization_msgs/msg/marker_array.hpp"

class AnalyzerNode : public rclcpp::Node {
public:
  AnalyzerNode() : Node("analyzer_node") {
    subscription_ = this->create_subscription<std_msgs::msg::String>(
      "char_stream", 10, std::bind(&AnalyzerNode::topic_callback, this, std::placeholders::_1));
    marker_pub_ = this->create_publisher<visualization_msgs::msg::MarkerArray>("visualization_marker_array", 10);
  }

private:
  void topic_callback(const std_msgs::msg::String::SharedPtr msg) {
    std::string s = msg->data;
    std::vector<int> last_seen(256, -1);
    int start = 0;

    // Pass 1: Find the current sliding window bounds
    for (int i = 0; i < (int)s.length(); i++) {
      if (last_seen[s[i]] >= start) start = last_seen[s[i]] + 1;
      last_seen[s[i]] = i;
    }

    // Pass 2: Create visual markers
    visualization_msgs::msg::MarkerArray marker_array;
    for (int i = 0; i < (int)s.length(); i++) {
      marker_array.markers.push_back(create_marker(i, s[i], (i >= start)));
    }
    marker_pub_->publish(marker_array);
  }

  visualization_msgs::msg::Marker create_marker(int index, char c, bool is_green) {
    visualization_msgs::msg::Marker m;
    m.header.frame_id = "map";
    m.header.stamp = this->now();
    m.ns = "dsa_viz";
    m.id = index;
    m.type = visualization_msgs::msg::Marker::CUBE;
    m.action = visualization_msgs::msg::Marker::ADD;
    m.pose.position.x = index * 1.2;
    m.scale.x = 1.0; m.scale.y = 1.0; m.scale.z = 1.0;
    m.color.a = 1.0;
    if (is_green) { m.color.g = 1.0; } else { m.color.r = 1.0; }
    return m;
  }

  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
  rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr marker_pub_;
};

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<AnalyzerNode>());
  rclcpp::shutdown();
  return 0;
}