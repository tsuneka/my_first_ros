import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist


class TB3SquareDriver(Node):
    def __init__(self) -> None:
        super().__init__("tb3_square_driver")

        self.publisher_ = self.create_publisher(Twist, "/cmd_vel", 10)
        self.timer = self.create_timer(0.1, self.timer_callback)

        # 状態管理
        self.mode = "forward"
        self.mode_time = 0.0

        # 調整しやすいパラメータ
        self.forward_speed = 0.15
        self.turn_speed = 0.5
        self.forward_duration = 4.0
        self.turn_duration = 3.2

        self.get_logger().info("TB3 square driver started.")

    def timer_callback(self) -> None:
        dt = 0.1
        self.mode_time += dt

        cmd = Twist()

        if self.mode == "forward":
            cmd.linear.x = self.forward_speed
            cmd.angular.z = 0.0
            if self.mode_time >= self.forward_duration:
                self.mode = "turn"
                self.mode_time = 0.0
                self.get_logger().info("Switch to TURN")

        elif self.mode == "turn":
            cmd.linear.x = 0.0
            cmd.angular.z = self.turn_speed
            if self.mode_time >= self.turn_duration:
                self.mode = "forward"
                self.mode_time = 0.0
                self.get_logger().info("Switch to FORWARD")

        self.publisher_.publish(cmd)


def main(args=None) -> None:
    rclpy.init(args=args)
    node = TB3SquareDriver()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        # 終了時に停止命令
        stop_msg = Twist()
        node.publisher_.publish(stop_msg)
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()