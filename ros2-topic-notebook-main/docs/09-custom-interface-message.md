# 09. 自定义接口消息：定义、生成与使用

本节在已有 String 示例之外，演示如何定义自己的消息类型，并让 C++ 发布者和订阅者使用它。示例独立存放于 examples/custom_message_workspace/，不改动仓库原有 src/。

## 1. 为什么需要自定义消息

标准消息适合通用数据，例如 std_msgs/msg/String。实际项目往往需要同时传递多个有明确含义的字段。此时可定义 .msg 文件，由 ROS 2 的接口生成工具生成对应语言的类型支持。

## 2. 定义消息

文件：topic_demo_interfaces/msg/Student.msg

```text
string name
int32 age
float32 score
bool passed
```

每行由字段类型和字段名组成。ROS 2 接口定义使用的类型包括 bool、int32、float32、string 等。字段名采用小写下划线风格是较常见的约定。

## 3. 创建接口功能包

接口包的 CMakeLists.txt：

```cmake
cmake_minimum_required(VERSION 3.8)
project(topic_demo_interfaces)

find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/Student.msg"
)

ament_export_dependencies(rosidl_default_runtime)
ament_package()
```

package.xml 需要声明接口生成器、运行时依赖和接口包组：

```xml
<?xml version="1.0"?>
<package format="3">
  <name>topic_demo_interfaces</name>
  <version>0.0.1</version>
  <description>Custom Student message for ROS 2 topic learning</description>
  <maintainer email="student@example.com">student</maintainer>
  <license>Apache-2.0</license>
  <buildtool_depend>ament_cmake</buildtool_depend>
  <build_depend>rosidl_default_generators</build_depend>
  <exec_depend>rosidl_default_runtime</exec_depend>
  <member_of_group>rosidl_interface_packages</member_of_group>
  <export><build_type>ament_cmake</build_type></export>
</package>
```

## 4. 编译与检查接口

将示例中的 topic_demo_interfaces 和 topic_demo_cpp 两个包复制到工作空间的 src/，然后：

```bash
cd ~/ros2_custom_ws
colcon build --packages-select topic_demo_interfaces
. install/setup.bash
ros2 interface show topic_demo_interfaces/msg/Student
```

接口包必须先于依赖它的 C++ 包完成构建；colcon 通常会根据 package.xml 依赖关系安排顺序。

## 5. 发布和订阅

发布者创建 topic_demo_interfaces::msg::Student 对象，逐个设置 name、age、score、passed 字段，再调用 publish()。订阅者的回调参数类型也必须是同一个消息类型。示例节点发布到 /student_info。

```bash
ros2 topic list
ros2 topic info /student_info
ros2 topic echo /student_info
```

## 6. 常见错误

- 找不到消息头文件：确认接口包构建成功，且在编译 C++ 包前已声明依赖。
- ros2 interface show 找不到接口：确认已 source 当前工作空间的 install/setup.bash。
- 发布端和订阅端无数据：检查话题名、消息类型、QoS 和两个节点是否同时运行。
- 不要把自定义消息文件放进原有 src/ 目录覆盖参考内容；按 README 的复制步骤使用独立工作空间。

参考：[ROS 2 Humble 自定义接口官方教程](https://docs.ros.org/en/humble/Tutorials/Beginner-Client-Libraries/Custom-ROS2-Interfaces.html)。
