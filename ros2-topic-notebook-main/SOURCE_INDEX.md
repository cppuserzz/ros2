# 源码与文档索引

## 原有参考源码（保持原样）

本次更新不修改仓库根目录下的 src/ 及其任何文件。

- src/topic_demo_cpp/src/talker.cpp：定时发布 std_msgs/msg/String 的节点。
- src/topic_demo_cpp/src/listener.cpp：订阅 /chatter 并打印消息的节点。
- src/topic_demo_cpp/CMakeLists.txt：定义依赖、可执行目标和安装规则。
- src/topic_demo_cpp/package.xml：功能包元数据与依赖声明。

## 新增自定义消息示例

- examples/custom_message_workspace/topic_demo_interfaces/msg/Student.msg：学生信息消息定义。
- examples/custom_message_workspace/topic_demo_interfaces/CMakeLists.txt：生成消息接口的构建规则。
- examples/custom_message_workspace/topic_demo_interfaces/package.xml：接口生成器与运行时依赖。
- examples/custom_message_workspace/topic_demo_cpp/src/custom_talker.cpp：周期发布 Student 消息。
- examples/custom_message_workspace/topic_demo_cpp/src/custom_listener.cpp：订阅并打印 Student 消息。
- examples/custom_message_workspace/topic_demo_cpp/CMakeLists.txt：构建自定义消息发布者和订阅者。
- examples/custom_message_workspace/topic_demo_cpp/package.xml：声明 rclcpp 与接口包依赖。

## 文档

- docs/01-ros2-basics.md：节点、话题、消息、Topic/Service/Action 区别。
- docs/02-workspace-and-package.md：工作空间与创建功能包。
- docs/03-build-and-run.md：rosdep、colcon、source、ros2 run。
- docs/04-topic-cli.md：topic list/info/echo/hz/pub、node 命令。
- docs/05-code-walkthrough.md：发布订阅 C++ 代码解释。
- docs/06-qos-and-naming.md：QoS、相对/绝对名称和 remapping。
- docs/07-troubleshooting.md：常见错误排查。
- docs/08-exercises.md：动手练习与自测。
- docs/09-custom-interface-message.md：自定义 .msg、接口包、构建和使用。
- docs/10-command-cheatsheet.md：环境与话题通信常用命令速查。
