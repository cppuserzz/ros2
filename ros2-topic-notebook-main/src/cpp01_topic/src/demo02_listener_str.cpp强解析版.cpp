// 引入ROS2的C++核心库头文件，节点、订阅、日志、spin都依赖这个
#include "rclcpp/rclcpp.hpp"
// 引入ROS2标准字符串消息类型头文件，std_msgs/msg/String
#include "std_msgs/msg/string.hpp"
// 使用std命名空间，后续std相关可以省略std::
using namespace std;

// 自定义订阅节点类listener，公有继承ROS2节点基类rclcpp::Node
class listener : public rclcpp::Node
{
private:
    // 订阅器智能指针，模板参数<std_msgs::msg::String>代表订阅字符串消息
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;

    // 消息回调函数：收到话题消息时自动执行这个函数
    void do_callback(const std_msgs::msg::String& msg)
    {
        // RCLCPP_INFO：ROS信息日志打印宏
        // this->get_logger() 获取当前节点的日志器
        // %s 字符串占位符；msg.data.c_str() 把std::string转C风格char*
        RCLCPP_INFO(this->get_logger(),"订阅到的消息是: %s",msg.data.c_str());
    }
public:
    // 构造函数：节点创建时自动执行，初始化列表调用父类Node构造，设置节点名listener_node_cpp
    listener():Node("listener_node_cpp")
    {
        // 打印日志：订阅节点已经创建成功
        RCLCPP_INFO(this->get_logger(),"订阅方创建");

        // 创建订阅器
        // 参数1：话题名称 chatter，发布方话题名必须一致才能通信
        // 参数2：QoS队列深度10，最多缓存10条未处理消息
        // 参数3：bind绑定回调函数，this代表当前实例，placeholders::_1是占位符，收到的消息传给回调第一个形参
        subscription_ = this->create_subscription<std_msgs::msg::String>("chatter",10,bind(&listener::do_callback,this,placeholders::_1));
    }
};

// 程序入口main函数
int main(int argc,char const* argv[])
{
    // 初始化ROS2上下文，启动底层DDS通信、解析ros命令行参数
    rclcpp::init(argc,argv);
    // 创建listener节点智能指针，rclcpp::spin开启阻塞事件循环，等待消息触发回调
    rclcpp::spin(make_shared<listener>());
    // 关闭ROS2上下文，释放通信资源
    rclcpp::shutdown();
    // 程序正常退出，返回0
    return 0;
}
