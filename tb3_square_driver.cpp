#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"

class TB3SquareDriver : public rclcpp::Node
{
public:
  TB3SquareDriver() : Node("tb3_square_driver")
  {
    publisher_ =
      this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);

    timer_ = this->create_wall_timer(
      std::chrono::milliseconds(100),
      std::bind(&TB3SquareDriver::timer_callback, this));

    mode_ = "forward";
    mode_time_ = 0.0;

    forward_speed_ = 0.15;
    turn_speed_ = 0.5;

    forward_duration_ = 4.0;
    turn_duration_ = 3.2;

    RCLCPP_INFO(this->get_logger(), "TB3 square driver started.");
  }

private:
  void timer_callback()
  {
    double dt = 0.1;
    mode_time_ += dt;

    geometry_msgs::msg::Twist cmd;

    if (mode_ == "forward")
    {
      cmd.linear.x = forward_speed_;

      if (mode_time_ >= forward_duration_)
      {
        mode_ = "turn";
        mode_time_ = 0.0;
        RCLCPP_INFO(this->get_logger(), "Switch to TURN");
      }
    }
    else if (mode_ == "turn")
    {
      cmd.angular.z = turn_speed_;

      if (mode_time_ >= turn_duration_)
      {
        mode_ = "forward";
        mode_time_ = 0.0;
        RCLCPP_INFO(this->get_logger(), "Switch to FORWARD");
      }
    }

    publisher_->publish(cmd);
  }

  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;

  std::string mode_;
  double mode_time_;

  double forward_speed_;
  double turn_speed_;

  double forward_duration_;
  double turn_duration_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  auto node = std::make_shared<TB3SquareDriver>();

  rclcpp::spin(node);

  geometry_msgs::msg::Twist stop_msg;
  node->get_node_topics_interface(); 

  rclcpp::shutdown();
  return 0;
}