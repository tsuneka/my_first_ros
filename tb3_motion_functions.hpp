#ifndef TB3_MOTION_FUNCTIONS_HPP_
#define TB3_MOTION_FUNCTIONS_HPP_

#include "geometry_msgs/msg/twist.hpp"

geometry_msgs::msg::Twist make_stop_cmd();
geometry_msgs::msg::Twist make_forward_cmd(double speed);
geometry_msgs::msg::Twist make_turn_left_cmd(double speed);
geometry_msgs::msg::Twist make_turn_right_cmd(double speed);
geometry_msgs::msg::Twist make_diagonal_cmd(double linear_speed, double angular_speed);
geometry_msgs::msg::Twist make_stop_cmd();


#endif  // TB3_MOTION_FUNCTIONS_HPP_
