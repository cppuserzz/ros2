# 贡献与维护指南

欢迎通过 Issue 或 Pull Request 补充命令解释、修正错误或添加小型可运行示例。

## 建议

- 文档使用 Markdown，代码块标注语言。
- 命令注明适用的 ROS 2 发行版；本项目默认以 Humble 为例。
- 新增 C++ 节点时同步检查 `package.xml` 和 `CMakeLists.txt`。
- 修改代码后在干净的 ROS 2 工作空间中运行 `colcon build` 验证。
- 避免提交 `build/`、`install/`、`log/` 等生成目录。
- 对外部教程进行总结时请链接原始资料，不要直接复制大段受版权保护的内容。
