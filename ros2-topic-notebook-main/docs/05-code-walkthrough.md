# 05. C++ 代码逐段解读

## 发布者的核心逻辑

```cpp
publisher_ = this->create_publisher<std_msgs::msg::String>("chatter", 10);
timer_ = this->create_wall_timer(
  1s, std::bind(&Talker::timer_callback, this));
```

- `create_publisher<消息类型>()` 创建发布器。
- `"chatter"` 是相对话题名，在默认命名空间下通常解析为 `/chatter`。
- `10` 是简化 QoS 参数中的历史队列深度，不是发布次数。
- `create_wall_timer(1s, ...)` 约每秒触发一次回调。
- `std::bind(&Talker::timer_callback, this)` 将当前对象的成员函数绑定为可调用对象。

回调中构造消息并发布：

```cpp
std_msgs::msg::String message;
message.data = "Hello ROS 2: " + std::to_string(count_++);
RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
publisher_->publish(message);
```

`count_++` 使用旧值生成当前序号，然后将成员变量加一。`RCLCPP_INFO` 输出日志；`publish()` 发送消息。

## 订阅者的核心逻辑

```cpp
subscription_ = this->create_subscription<std_msgs::msg::String>(
  "chatter", 10,
  std::bind(&Listener::topic_callback, this, std::placeholders::_1));
```

- `create_subscription` 创建订阅器。
- 话题名和消息类型要与发布端匹配。
- `std::placeholders::_1` 为回调的第一个参数留出位置，收到消息时由 ROS 2 传入消息对象。
- 回调通过 `message->data` 读取字符串。

订阅者不需要不断轮询话题。`rclcpp::spin()` 持续处理事件；消息到达后，ROS 2 调度相应回调。

## 为什么保存智能指针成员？

`publisher_`、`subscription_` 和 `timer_` 作为节点的成员存在，使通信实体和定时器在节点生命周期内持续有效。若只在构造函数中创建局部对象，函数结束后对象可能被销毁。

## main() 的生命周期

```cpp
rclcpp::init(argc, argv);
rclcpp::spin(std::make_shared<Talker>());
rclcpp::shutdown();
```

- `init` 初始化 ROS 2 客户端库。
- `make_shared` 创建并用共享指针管理节点。
- `spin` 持续处理回调，直到节点退出或收到中断信号。
- `shutdown` 关闭 ROS 2 客户端库。

## CMake 为什么需要 install？

`add_executable(talker ...)` 定义可执行目标，`ament_target_dependencies` 关联依赖，`install(TARGETS ...)` 把程序安装到 `lib/${PROJECT_NAME}`。这让 `ros2 run <包名> <可执行名>` 能按 ROS 2 包的约定找到它。
