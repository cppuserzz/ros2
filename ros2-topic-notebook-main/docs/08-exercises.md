# 08. 动手练习

## 练习 1：改变发布频率

把 talker 的定时周期从 `1s` 改为 `500ms`，重新构建，再运行：

```bash
ros2 topic hz /chatter
```

解释为什么实际测量值不一定恰好是 2 Hz。

## 练习 2：修改消息内容

修改字符串内容，重新构建，并使用 `ros2 topic echo /chatter` 检查。

## 练习 3：命令行发布

启动 listener 后执行：

```bash
ros2 topic pub --once /chatter std_msgs/msg/String "{data: 'Message from terminal'}"
```

再尝试 `--rate 5`，比较一次性发布和持续发布的区别。

## 练习 4：添加第二个订阅者

新增一个订阅 `/chatter` 的节点，验证一个发布者可以同时服务多个订阅者。

## 练习 5：话题重映射

将 talker 的 `chatter` 重映射到 `/demo/chatter`，观察原 listener 的表现，并解释原因。

## 练习 6：故意写错话题名

临时把订阅端话题改成 `other_topic`，重新编译并排查。完成后恢复代码。

## 练习 7：自定义消息（进阶）

尝试定义包含 `string name`、`int32 id` 的 ROS 2 消息。该练习需要接口包和构建配置；仅在 `.cpp` 中定义普通 C++ struct 并不能自动成为 ROS 2 消息类型。

## 自测

1. Topic 和 Service 有什么区别？
2. 为什么发布者与订阅者的消息类型要兼容？
3. `colcon build` 与 `source install/setup.bash` 分别做什么？
4. `ros2 run topic_demo_cpp talker` 的三个部分各是什么？
5. 为什么能列出话题但收不到消息？
6. `create_publisher(..., 10)` 中的 `10` 表示什么？
