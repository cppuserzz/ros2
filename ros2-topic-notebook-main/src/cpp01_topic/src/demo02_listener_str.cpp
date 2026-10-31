#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
using namespace std;

class listener : public rclcpp::Node
{
private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;

    //回调函数
    void do_callback(const std_msgs::msg::String& msg)
    {
        //输出订阅到的消息
        RCLCPP_INFO(this->get_logger(),"订阅到的消息是: %s",msg.data.c_str());
    }
public:
    listener():Node("listener_node_cpp")
    {
        RCLCPP_INFO(this->get_logger(),"订阅方创建");
        //创建订阅方
        subscription_ = this->create_subscription<std_msgs::msg::String>("chatter",10,bind(&listener::do_callback,this,placeholders::_1));//订阅的topic,qos队列长度，callback回调函数   传入的回调函数的参数用占位符
    }
};



int main(int argc,char const* argv[])
{
    rclcpp::init(argc,argv);
    rclcpp::spin(make_shared<listener>());
    rclcpp::shutdown();
    return 0;
}