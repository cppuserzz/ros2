# 10. ROS 2 命令速查表

以下命令以 Ubuntu 22.04 + ROS 2 Humble 为例。每个新终端通常都要加载 ROS 2 环境；使用自己工作空间构建的包时，还要加载该工作空间。

## 环境与工作空间

```bash
source /opt/ros/humble/setup.bash
printenv | grep ROS
ros2 doctor
mkdir -p ~/ros2_ws/src
cd ~/ros2_ws
colcon build
source install/setup.bash
```

## 功能包

```bash
ros2 pkg list
ros2 pkg prefix rclcpp
ros2 pkg create --build-type ament_cmake --dependencies rclcpp std_msgs my_cpp_pkg
rosdep install --from-paths src --ignore-src -r -y --rosdistro humble
colcon build --packages-select my_cpp_pkg
colcon build --symlink-install
```

## 节点

```bash
ros2 node list
ros2 node info /talker
ros2 run <package_name> <executable_name>
```

## 话题与消息

```bash
ros2 topic list
ros2 topic list -t
ros2 topic info /chatter
ros2 topic info /chatter --verbose
ros2 topic echo /chatter
ros2 topic hz /chatter
ros2 topic bw /chatter
ros2 topic pub /chatter std_msgs/msg/String "{data: 'hello'}"
ros2 topic pub --once /chatter std_msgs/msg/String "{data: 'one shot'}"
ros2 interface list
ros2 interface show std_msgs/msg/String
```

## 调试顺序建议

1. ros2 node list：节点是否启动？
2. ros2 topic list -t：话题名和消息类型是否正确？
3. ros2 topic info /topic_name --verbose：发布者、订阅者与 QoS 是什么？
4. ros2 topic echo /topic_name：消息是否真的流动？
5. 检查每个终端是否 source 了正确环境，以及节点是否被 remap 到其他话题。

## 注意

- 命令中的尖括号参数是占位符，运行时需替换成实际名称。
- YAML 字符串字段需要正确引号；复杂消息可先用 ros2 interface show 查看字段。
- ros2 topic pub 默认会持续发布；使用 --once 只发一条。
- 同一话题的发布者和订阅者需要消息类型兼容，QoS 也要匹配。
