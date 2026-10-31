# 04. 话题命令行工具

启动 talker 和 listener 后，在另一个已加载 ROS 2 环境的终端操作。

## 列出话题和类型

```bash
ros2 topic list
ros2 topic list -t
```

`-t` 会显示消息类型。结果会因当前运行的节点而不同。

## 查看话题信息

```bash
ros2 topic info /chatter
ros2 topic info /chatter --verbose
```

可以查看消息类型、发布者/订阅者数量；详细模式还会显示端点的 QoS 信息。

## 查看实时消息

```bash
ros2 topic echo /chatter
```

命令会订阅话题并打印收到的消息。按 `Ctrl+C` 结束。

## 查看消息频率

```bash
ros2 topic hz /chatter
```

本项目目标频率约为 1 Hz；实际测量会受调度和系统负载影响。

## 从命令行发布消息

发布一次：

```bash
ros2 topic pub --once /chatter std_msgs/msg/String "{data: 'Hello from CLI'}"
```

持续以约 2 Hz 发布：

```bash
ros2 topic pub --rate 2 /chatter std_msgs/msg/String "{data: 'CLI message'}"
```

参数依次是发布命令、频率选项、话题名、消息类型和消息内容。命令行发布者和代码中的 talker 可以同时向同一话题发布，listener 会收到两边的消息。

## 查看接口定义

```bash
ros2 interface show std_msgs/msg/String
```

## 节点相关命令

```bash
ros2 node list
ros2 node info /topic_demo_talker
ros2 node info /topic_demo_listener
```

节点名称由代码中的 `Node("...")` 决定。若名称不同，先用 `ros2 node list` 查询实际名称。

## 推荐排查顺序

1. `ros2 node list`：节点是否启动。
2. `ros2 topic list -t`：话题名称和类型是否正确。
3. `ros2 topic info /chatter --verbose`：是否有发布者/订阅者、QoS 是否兼容。
4. `ros2 topic echo /chatter`：消息是否实际到达。
5. `ros2 topic hz /chatter`：发布频率是否符合预期。
