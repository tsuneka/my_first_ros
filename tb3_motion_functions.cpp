#include "tb3_motion_functions.hpp"

geometry_msgs::msg::Twist make_stop_cmd()
{
  return geometry_msgs::msg::Twist();
}

geometry_msgs::msg::Twist make_forward_cmd(double speed)
{
  geometry_msgs::msg::Twist cmd;
  cmd.linear.x = speed;
  return cmd;
}

geometry_msgs::msg::Twist make_turn_left_cmd(double speed)
{
  geometry_msgs::msg::Twist cmd;
  cmd.angular.z = speed;
  return cmd;
}

geometry_msgs::msg::Twist make_turn_right_cmd(double speed)
{
  geometry_msgs::msg::Twist cmd;
  cmd.angular.z = -speed;
  return cmd;
}

geometry_msgs::msg::Twist make_diagonal_cmd(double linear_speed, double angular_speed)
{
  geometry_msgs::msg::Twist cmd;
  cmd.linear.x = linear_speed;
  cmd.angular.z = angular_speed;
  return cmd;
}
