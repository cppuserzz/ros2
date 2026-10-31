# 07. 常见问题排查

## `ros2: command not found`

```bash
source /opt/ros/humble/setup.bash
which ros2
```

若脚本不存在，请检查 ROS 2 是否安装，以及实际发行版路径是否为 `humble`。

## `Package 'topic_demo_cpp' not found`

```bash
cd ~/ros2_ws
colcon build --packages-select topic_demo_cpp
source install/setup.bash
ros2 pkg list | grep topic_demo_cpp
```

确认包在 `~/ros2_ws/src/topic_demo_cpp`，构建没有失败，并且当前终端加载了工作空间环境。

## `No executable found`

检查 `CMakeLists.txt` 是否定义了 `add_executable`，是否关联依赖，以及是否在 `install(TARGETS ...)` 中安装目标。修改后重新构建并 source。

## 找不到头文件

若找不到 `rclcpp/rclcpp.hpp` 或 `std_msgs/msg/string.hpp`，检查是否加载 ROS 2 环境、依赖是否安装，以及 `package.xml` 和 `CMakeLists.txt` 是否正确声明依赖。

## 节点运行但 listener 没有输出

```bash
ros2 node list
ros2 topic list -t
ros2 topic info /chatter --verbose
ros2 topic echo /chatter
```

检查发布者是否运行、话题名和消息类型是否一致、QoS 是否兼容，以及两个终端的 `ROS_DOMAIN_ID` 是否一致。

## 两台机器无法发现节点

检查网络连通性、DDS/RMW 配置、防火墙、Wi-Fi 客户端隔离和多网卡环境。查看环境变量：

```bash
echo "$ROS_DOMAIN_ID"
echo "$RMW_IMPLEMENTATION"
```

默认情况下 `ROS_DOMAIN_ID` 为空时使用默认域。不要无故修改；互相通信的节点需要采用一致的域配置。

## 清理后重建

```bash
cd ~/ros2_ws
rm -rf build/topic_demo_cpp install/topic_demo_cpp log
colcon build --packages-select topic_demo_cpp
source install/setup.bash
```

执行删除命令前，确认当前目录是正确的工作空间。
