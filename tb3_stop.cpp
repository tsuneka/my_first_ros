#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"

class TB3Stop : public rclcpp::Node
{
public:
  TB3Stop() : Node("tb3_stop")
  {
    publisher_ =
      this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);

    timer_ = this->create_wall_timer(
      std::chrono::milliseconds(500),
      std::bind(&TB3Stop::timer_callback, this));
  }

private:
  void timer_callback()
  {
    geometry_msgs::msg::Twist msg;

    publisher_->publish(msg);

    RCLCPP_INFO(this->get_logger(), "Publishing stop command...");
  }

  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TB3Stop>());
  rclcpp::shutdown();
  return 0;
}