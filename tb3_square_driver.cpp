#include "rclcpp/rclcpp.hpp"
#include "tb3_motion_functions.hpp"

// Change these numbers first.
const double ForwardSpeed = 0.15;
const double TurnSpeed = 0.50;
const double ForwardTime = 4.0;
const double TurnTime = 3.2;
const double TimerPeriod = 0.1;

class TB3SquareDriver : public rclcpp::Node
{
public:
  TB3SquareDriver() : Node("tb3_square_driver")
  {
    cmd_vel_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);

    timer_ = this->create_wall_timer(
      std::chrono::duration<double>(TimerPeriod),
      std::bind(&TB3SquareDriver::timer_callback, this));

    is_turning_ = false;
    elapsed_time_ = 0.0;

    RCLCPP_INFO(this->get_logger(), "tb3_square_driver started");
    RCLCPP_INFO(this->get_logger(), "robot moves forward, then turns left");
  }

private:
  void timer_callback()
  {
    if (is_turning_) {
      cmd_vel_pub_->publish(make_turn_left_cmd(TurnSpeed));
    } else {
      cmd_vel_pub_->publish(make_forward_cmd(ForwardSpeed));
    }

    elapsed_time_ += TimerPeriod;

    if (!is_turning_ && elapsed_time_ >= ForwardTime) {
      is_turning_ = true;
      elapsed_time_ = 0.0;
      RCLCPP_INFO(this->get_logger(), "turn");
    } else if (is_turning_ && elapsed_time_ >= TurnTime) {
      is_turning_ = false;
      elapsed_time_ = 0.0;
      RCLCPP_INFO(this->get_logger(), "forward");
    }
  }

  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_pub_;
  rclcpp::TimerBase::SharedPtr timer_;
  bool is_turning_;
  double elapsed_time_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<TB3SquareDriver>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
