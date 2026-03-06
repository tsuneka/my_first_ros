import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist


class TB3Stop(Node):
    def __init__(self) -> None:
        super().__init__("tb3_stop")
        self.publisher_ = self.create_publisher(Twist, "/cmd_vel", 10)
        self.timer = self.create_timer(0.5, self.timer_callback)

    def timer_callback(self) -> None:
        msg = Twist()
        self.publisher_.publish(msg)
        self.get_logger().info("Publishing stop command...")


def main(args=None) -> None:
    rclpy.init(args=args)
    node = TB3Stop()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()