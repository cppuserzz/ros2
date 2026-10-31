# 02. 工作空间与功能包

## 工作空间结构

```text
ros2_ws/
├── src/       # 功能包源码
├── build/     # 编译中间文件
├── install/   # 安装后的包和环境脚本
└── log/       # 编译日志
```

创建工作空间：

```bash
mkdir -p ~/ros2_ws/src
cd ~/ros2_ws/src
colcon build
```

## 从零创建 C++ 包

```bash
ros2 pkg create --build-type ament_cmake topic_demo_cpp --dependencies rclcpp std_msgs --node-name 程序名字
```

参数含义：

- `ros2 pkg create`：创建功能包。
- `--build-type ament_cmake`：使用 ROS 2 的 CMake 构建体系。
- `topic_demo_cpp`：包名。
- `--dependencies rclcpp std_msgs`：声明本例依赖的 ROS 2 C++ 客户端库和标准消息包。
- - `--node-name 程序名字`：在该功能包底下创建一个 程序名字 源码文件。

本仓库已经提供完整功能包，通常直接复制 `src/topic_demo_cpp` 即可，不必重复创建。

## 三个重要文件

- `package.xml`：包元数据、许可证和依赖声明。
- `CMakeLists.txt`：查找依赖、定义可执行目标、配置安装规则。
- `src/*.cpp`：节点源代码。

## 为什么要 source？

```bash
source /opt/ros/humble/setup.bash
source ~/ros2_ws/install/setup.bash
```

第一条加载 ROS 2 安装环境；第二条加载当前工作空间编译出的包环境。`source` 会在当前终端设置环境变量和包索引。新开的终端通常也需要执行这两条命令。
