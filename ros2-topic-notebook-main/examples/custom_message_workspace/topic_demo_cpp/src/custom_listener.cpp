#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "topic_demo_interfaces/msg/student.hpp"

class CustomListener : public rclcpp::Node
{
public:
  CustomListener() : Node("custom_listener")
  {
    subscription_ = create_subscription<topic_demo_interfaces::msg::Student>(
      "/student_info", 10,
      [this](topic_demo_interfaces::msg::Student::ConstSharedPtr message) {
        RCLCPP_INFO(get_logger(), "Receive name=%s age=%d score=%.1f passed=%s",
          message->name.c_str(), message->age, message->score,
          message->passed ? "true" : "false");
      });
  }

private:
  rclcpp::Subscription<topic_demo_interfaces::msg::Student>::SharedPtr subscription_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<CustomListener>());
  rclcpp::shutdown();
  return 0;
}
