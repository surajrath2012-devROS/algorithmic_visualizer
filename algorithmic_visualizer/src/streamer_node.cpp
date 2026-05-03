#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class StreamerNode : public rclcpp::Node {
public:
  StreamerNode() : Node("streamer_node") {
    publisher_ = this->create_publisher<std_msgs::msg::String>("char_stream", 10);
    timer_ = this->create_wall_timer(1000ms, std::bind(&StreamerNode::timer_callback, this));
  }

private:
  void timer_callback() {
    auto message = std_msgs::msg::String();
    // Logic: Send a growing prefix of the string
    message.data = full_string.substr(0, current_index + 1);
    
    RCLCPP_INFO(this->get_logger(), "Streaming: '%s'", message.data.c_str());
    publisher_->publish(message);

    current_index = (current_index + 1) % (full_string.length() + 1);
    if (current_index == 0) current_index = 0; 
  }

  std::string full_string = "abcabcbb";
  size_t current_index = 0;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<StreamerNode>());
  rclcpp::shutdown();
  return 0;
}