#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class SimpleTalker : public rclcpp::Node
{
public:
  SimpleTalker() : Node("simple_talker"), count_(0)
  {
    publisher_ = this->create_publisher<std_msgs::msg::String>("chatter", 10);

    timer_ = this->create_wall_timer(
      std::chrono::seconds(1),
      std::bind(&SimpleTalker::timer_callback, this));
  }

private:
  void timer_callback()
  {
    auto msg = std_msgs::msg::String();
    msg.data = "Hello ROS2! count=" + std::to_string(count_);

    publisher_->publish(msg);

    RCLCPP_INFO(this->get_logger(), "Publish: '%s'", msg.data.c_str());

    count_++;
  }

  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  int count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SimpleTalker>());
  rclcpp::shutdown();
  return 0;
}