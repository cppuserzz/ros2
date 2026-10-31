#include "rclcpp/rclcpp.hpp"
#include "base_interface/msg/student.hpp"
using namespace std;

//自定义节点
class stu_listener : public rclcpp::Node
{
private:
    rclcpp::Subscription<base_interface::msg::Student>::SharedPtr subscrption_;

    void do_cb(const base_interface::msg::Student& msg)
    {
        //输出服务端发出的消息
        RCLCPP_INFO(this->get_logger(),"订阅到的消息是: {%s,%d,%.2f}",msg.name.c_str(),msg.age,msg.height);
    }
public:
    stu_listener():Node("stulistener_node_cpp")
    {
        RCLCPP_INFO(this->get_logger(),"订阅节点创建");
        subscrption_ = this->create_subscription<base_interface::msg::Student>("chatter_stu",10,bind(&stu_listener::do_cb,this,placeholders::_1));
    }

};



int main(int argc,char const* argv[])
{
	rclcpp::init(argc,argv);
	rclcpp::spin(make_shared<stu_listener>());  //回旋函数，代码执行到这一段将调用callback
  	rclcpp::shutdown();
  	return 0;
}