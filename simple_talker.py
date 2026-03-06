import rclpy
from rclpy.node import Node
from std_msgs.msg import String


class SimpleTalker(Node):
    def __init__(self) -> None:
        super().__init__("simple_talker")
        self.publisher_ = self.create_publisher(String, "chatter", 10)
        self.timer = self.create_timer(1.0, self.timer_callback)
        self.count = 0

    def timer_callback(self) -> None:
        msg = String()
        msg.data = f"Hello ROS 2! count={self.count}"
        self.publisher_.publish(msg)
        self.get_logger().info(f'Publish: "{msg.data}"')
        self.count += 1


def main(args=None) -> None:
    rclpy.init(args=args)
    node = SimpleTalker()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()