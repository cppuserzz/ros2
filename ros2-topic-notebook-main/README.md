# ROS 2 话题通信学习手册

面向初学者的 ROS 2 Topic 通信实践项目，参考 [ROS2 理论与实践课程](https://rzl6.github.io/ROS2_Tuition/) 第一章环境与基础内容、第二章话题通信内容，并结合 ROS 2 Humble 官方文档补充命令、接口配置和调试方法。示例代码为独立教学示例，并非原课程代码的逐字复制。

> **保护约定：仓库现有 src/ 目录是参考源码，本次更新不会修改其中任何文件。** 新增的自定义消息示例放在 examples/custom_message_workspace/，编译时再复制到工作空间的 src/。

## 环境

- Ubuntu 22.04 + ROS 2 Humble
- C++ / ament_cmake
- rclcpp、std_msgs、自定义接口 topic_demo_interfaces/msg/Student

## 学习路线

1. [ROS 2 基础与环境](docs/01-ros2-basics.md)
2. [工作空间与功能包](docs/02-workspace-and-package.md)
3. [编译、加载与运行](docs/03-build-and-run.md)
4. [话题命令行工具](docs/04-topic-cli.md)
5. [C++ 发布订阅代码解读](docs/05-code-walkthrough.md)
6. [QoS 与话题命名](docs/06-qos-and-naming.md)
7. [常见问题排查](docs/07-troubleshooting.md)
8. [动手练习](docs/08-exercises.md)
9. [自定义接口消息：定义、生成与使用](docs/09-custom-interface-message.md)
10. [ROS 2 命令速查表](docs/10-command-cheatsheet.md)

## 原有源码：String 发布订阅

本仓库原有 src/ 目录保持原样。原有示例包 src/topic_demo_cpp/ 使用 std_msgs/msg/String。

```bash
source /opt/ros/humble/setup.bash
mkdir -p ~/ros2_ws/src
cp -r src/topic_demo_cpp ~/ros2_ws/src/
cd ~/ros2_ws
rosdep install --from-paths src --ignore-src -r -y --rosdistro humble
colcon build --packages-select topic_demo_cpp
source install/setup.bash
```

在两个已加载环境的终端分别运行：

```bash
ros2 run topic_demo_cpp talker
ros2 run topic_demo_cpp listener
```

## 自定义消息示例

新增示例位于 examples/custom_message_workspace/，不会覆盖原有 src/。复制到独立工作空间后编译：

```bash
source /opt/ros/humble/setup.bash
mkdir -p ~/ros2_custom_ws/src
cp -r examples/custom_message_workspace/topic_demo_interfaces ~/ros2_custom_ws/src/
cp -r examples/custom_message_workspace/topic_demo_cpp ~/ros2_custom_ws/src/
cd ~/ros2_custom_ws
rosdep install --from-paths src --ignore-src -r -y --rosdistro humble
colcon build --symlink-install
source install/setup.bash
ros2 interface show topic_demo_interfaces/msg/Student
```

终端 A：
```bash
source /opt/ros/humble/setup.bash
source ~/ros2_custom_ws/install/setup.bash
ros2 run topic_demo_cpp custom_talker
```

终端 B：
```bash
source /opt/ros/humble/setup.bash
source ~/ros2_custom_ws/install/setup.bash
ros2 run topic_demo_cpp custom_listener
```

详见 [自定义接口消息教程](docs/09-custom-interface-message.md)。

## 目录说明

- docs/：分章节 Markdown 笔记
- src/：原有参考源码，本次不修改
- examples/custom_message_workspace/：新增的自定义消息示例
- scripts/setup_workspace.sh：原有工作空间辅助脚本
- SOURCE_INDEX.md：源码与文档索引

## 参考资料

- [ROS2 理论与实践课程](https://rzl6.github.io/ROS2_Tuition/)
- [ROS 2 Humble 官方文档](https://docs.ros.org/en/humble/)
- [官方自定义 ROS 2 接口教程](https://docs.ros.org/en/humble/Tutorials/Beginner-Client-Libraries/Custom-ROS2-Interfaces.html)
- [官方 C++ 发布者与订阅者教程](https://docs.ros.org/en/humble/Tutorials/Beginner-Client-Libraries/Writing-A-Simple-Cpp-Publisher-And-Subscriber.html)
- [官方 Topic 概念说明](https://docs.ros.org/en/humble/Concepts/Basic/About-Topics.html)

本仓库是独立的学习笔记项目，与课程作者及 ROS 2 官方无隶属关系。许可信息见 LICENSE。
