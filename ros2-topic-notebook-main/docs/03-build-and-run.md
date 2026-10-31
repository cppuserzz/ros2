# 03. 编译、加载与运行

## 首次编译

```bash
cd ~/ros2_ws
source /opt/ros/humble/setup.bash
rosdep install --from-paths src --ignore-src -r -y --rosdistro humble
colcon build --packages-select topic_demo_cpp
source install/setup.bash
```

- `rosdep install`：安装源码包声明但系统缺少的依赖。
- `--from-paths src`：从 `src` 中的包读取依赖。
- `--ignore-src`：忽略工作空间源码包本身。
- `-r`：继续处理其他依赖，即使某些依赖失败。
- `-y`：自动确认安装操作。
- `colcon build`：构建工作空间。
- `--packages-select topic_demo_cpp`：选择构建该包。
- `source install/setup.bash`：让当前终端发现本工作空间中的包。

如果 `rosdep` 未初始化或网络不可用，依赖安装可能失败；依赖已经安装时，可以先尝试直接 `colcon build`，再根据错误补齐依赖。

## 运行节点

在两个独立终端中分别执行（两个终端都要加载环境）：

```bash
source /opt/ros/humble/setup.bash
source ~/ros2_ws/install/setup.bash
ros2 run topic_demo_cpp talker
```

另一个终端运行：

```bash
source /opt/ros/humble/setup.bash
source ~/ros2_ws/install/setup.bash
ros2 run topic_demo_cpp listener
```

语法为 `ros2 run <包名> <可执行程序名>`。`talker` 和 `listener` 是在 `CMakeLists.txt` 中定义的可执行目标。按 `Ctrl+C` 停止。

## 常用构建命令

```bash
colcon build
colcon build --packages-select topic_demo_cpp
colcon build --event-handlers console_direct+
colcon build --symlink-install
```

`--symlink-install` 可在适用的文件上使用符号链接，便于开发迭代，但修改 C++ 源码后仍需重新编译。修改 Markdown 不需要编译。
