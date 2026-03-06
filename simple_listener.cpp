#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class SimpleListener : public rclcpp::Node
{
public:
  SimpleListener() : Node("simple_listener")
  {
    subscription_ = this->create_subscription<std_msgs::msg::String>(
      "chatter",
      10,
      std::bind(&SimpleListener::listener_callback, this, std::placeholders::_1));
  }

private:
  void listener_callback(const std_msgs::msg::String::SharedPtr msg)
  {
    RCLCPP_INFO(this->get_logger(), "Receive: '%s'", msg->data.c_str());
  }

  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SimpleListener>());
  rclcpp::shutdown();
  return 0;
}