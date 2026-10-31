# 06. QoS 与话题命名

## QoS 是什么？

QoS（Quality of Service）定义通信策略，常见内容包括：

- **History / Depth**：历史消息策略与队列深度。
- **Reliability**：Reliable（可靠）或 Best Effort（尽力而为）。
- **Durability**：Volatile 或 Transient Local，影响后来加入的订阅者能否获得历史样本。
- **Deadline、Lifespan、Liveliness**：与更新时间约束、消息有效期和端点活性有关。

本项目使用 `create_publisher(..., 10)` 和 `create_subscription(..., 10)` 的简写形式。`10` 是历史队列深度，不代表完整 QoS 配置。

## 话题存在却收不到消息？

发布者与订阅者 QoS 必须兼容。例如传感器发布端可能使用 Best Effort，而订阅端请求 Reliable 时，组合可能不兼容。用下面命令查看端点配置：

```bash
ros2 topic info /chatter --verbose
```

## 相对话题名和绝对话题名

`"chatter"` 是相对名，在默认命名空间下通常解析为 `/chatter`；`"/chatter"` 是绝对名。命名空间和 remapping 可能改变最终名称。

```bash
ros2 run topic_demo_cpp talker --ros-args -r chatter:=/demo/chatter
```

此时订阅端也需要订阅重映射后的话题，或采用匹配的重映射规则。

## 不要混淆这些名称

- 功能包名：`topic_demo_cpp`
- 可执行程序名：`talker`
- 节点名：`topic_demo_talker`
- 话题名：`/chatter`
- 消息类型：`std_msgs/msg/String`

因此 `ros2 run topic_demo_cpp talker` 使用的是包名和可执行程序名，不是话题名。
