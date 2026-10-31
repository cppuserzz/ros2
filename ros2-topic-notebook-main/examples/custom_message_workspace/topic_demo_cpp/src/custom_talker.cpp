#include <chrono>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "topic_demo_interfaces/msg/student.hpp"

using namespace std::chrono_literals;

class CustomTalker : public rclcpp::Node
{
public:
  CustomTalker() : Node("custom_talker"), count_(0)
  {
    publisher_ = create_publisher<topic_demo_interfaces::msg::Student>("/student_info", 10);
    timer_ = create_wall_timer(1s, [this]() {
      topic_demo_interfaces::msg::Student message;
      message.name = "Student_" + std::to_string(count_);
      message.age = 18 + static_cast<int32_t>(count_ % 5);
      message.score = 80.0F + static_cast<float>(count_ % 20);
      message.passed = message.score >= 60.0F;
      RCLCPP_INFO(get_logger(), "Publish name=%s age=%d score=%.1f passed=%s",
        message.name.c_str(), message.age, message.score, message.passed ? "true" : "false");
      publisher_->publish(message);
      ++count_;
    });
  }

private:
  rclcpp::Publisher<topic_demo_interfaces::msg::Student>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  uint32_t count_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<CustomTalker>());
  rclcpp::shutdown();
  return 0;
}
