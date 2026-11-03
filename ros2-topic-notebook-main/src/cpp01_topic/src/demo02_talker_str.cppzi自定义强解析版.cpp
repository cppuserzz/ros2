// 引入ROS2 C++核心库，节点、发布器、定时器、日志、spin都在这里
#include "rclcpp/rclcpp.hpp"
// 引入【自定义消息】Student的头文件，这个头文件是编译base_interface包时自动生成的
#include "base_interface/msg/student.hpp"
// 开启std命名空间，省略std::（工程大项目不推荐，练习写代码方便）
using namespace std;

// 自定义节点类 Talker_stu，公有继承ROS2节点基类 rclcpp::Node
// ROS2所有节点都必须继承 rclcpp::Node
class Talker_stu : public rclcpp::Node
{
    // 私有成员：只能在这个类内部访问
private:
    // 年龄计数变量，每发一条消息age自增1
    int age = 0;
    // 发布器智能指针
    // 模板参数 <base_interface::msg::Student>：指定这个发布器发布的消息类型是自定义Student消息
    rclcpp::Publisher<base_interface::msg::Student>::SharedPtr publisher_;
    // 定时器智能指针，用来周期性触发回调函数
    rclcpp::TimerBase::SharedPtr timer_;

    // 定时器回调函数：时间到了自动执行这个函数
    void on_timer()
    {
        // 创建一条Student类型的消息对象
        auto message = base_interface::msg::Student();
        // 给消息里面的各个字段赋值（字段在Student.msg里面定义）
        message.name = "lihua";
        message.age = age++;    // 先把age赋值给消息，age再+1
        message.height = 2.2;

        // ROS日志打印
        // %s 字符串、%d整数、%.2f保留两位小数浮点数
        // message.name是std::string，printf系列日志只能接收C字符串，所以调用.c_str()转换
        RCLCPP_INFO(this->get_logger(), "服务端发布的消息： (%s,%d,%.2f)",
            message.name.c_str(), message.age, message.height);

        // 核心：把这条消息通过发布器发送到话题 chatter_stu
        publisher_->publish(message);
    }

    // 公有成员，外部可以访问
public:
    // 构造函数：创建节点对象的时候，自动执行构造函数
    // 初始化列表调用父类Node构造，设置节点名字：stu_talker_node_cpp
    Talker_stu() :Node("stu_talker_node_cpp")
    {
        // 打印日志，提示节点创建成功
        RCLCPP_INFO(this->get_logger(), "消息发布方创建");

        // 创建发布器
        // 参数1：话题名 chatter_stu，订阅方必须填写一模一样的话题名+一模一样的消息类型才能收到
        // 参数2：QoS队列深度 10，最多缓存10条来不及发送的消息，超过会丢弃旧消息
        publisher_ = this->create_publisher<base_interface::msg::Student>("chatter_stu", 10);

        // 创建定时器
        // 参数1：定时周期 500ms，每0.5s触发一次on_timer回调
        // 参数2：bind绑定回调函数，this代表当前Talker_stu实例
        timer_ = this->create_wall_timer(500ms, bind(&Talker_stu::on_timer, this));
    }
};

// C++程序入口函数
int main(int argc, char const* argv[])
{
    // 初始化ROS2上下文，启动底层DDS通信，解析ROS命令行参数
    // 一个进程里面只需要调用一次 rclcpp::init
    rclcpp::init(argc, argv);
    // 1. make_shared<Talker_stu>() 在堆上创建节点对象，返回智能指针
    // 2. rclcpp::spin() 阻塞循环（事件循环），等待定时器、订阅消息等事件，自动触发回调
    // 注释里叫回旋函数，就是spin
    rclcpp::spin(make_shared<Talker_stu>());
    // spin退出后执行，关闭ROS上下文，释放DDS通信资源
    rclcpp::shutdown();
    // 程序正常退出
    return 0;
}
