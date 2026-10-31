# 01. ROS 2 话题通信基础

## 节点（Node）

ROS 2 应用通常由多个节点组成，每个节点负责相对独立的任务，例如摄像头采集、图像识别、底盘控制或状态显示。节点可以通过 ROS 2 通信机制交换数据，不必直接调用对方的函数。

## 话题（Topic）

话题是一条以名称标识的数据流。发布者向话题发送消息，订阅者订阅该话题并接收消息。

```text
talker --Publisher--> /chatter --Subscriber--> listener
                    std_msgs/msg/String
```

- **Publisher 发布者**：创建发布器，通过 `publish()` 发送消息。
- **Subscriber 订阅者**：创建订阅器，收到新消息时执行回调函数。
- **Message 消息**：传输的数据结构，例如字符串、速度、图像或雷达数据。
- **Callback 回调**：消息到达等事件发生时，由 ROS 2 调用的函数。

发布者和订阅者不需要知道彼此的节点名称；话题名称、消息类型以及 QoS 等条件需要兼容。

## 本项目的消息类型

使用 `std_msgs/msg/String`，主要字段为 `data`：

```cpp
std_msgs::msg::String message;
message.data = "Hello ROS 2";
publisher_->publish(message);
```

查看接口：

```bash
ros2 interface list
ros2 interface show std_msgs/msg/String
```

## 话题、服务和动作的区别

Topic 适合持续更新的数据流，如传感器数据、里程计和状态信息。Service 更适合短时请求—响应；Action 适合持续时间较长、需要反馈进度或取消能力的任务。具体选择应根据任务交互方式决定。
