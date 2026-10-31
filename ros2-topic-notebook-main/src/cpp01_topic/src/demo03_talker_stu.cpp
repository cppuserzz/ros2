#include "rclcpp/rclcpp.hpp"
#include "base_interface/msg/student.hpp"
using namespace std;
// using namespace 

//自定义节点
class Talker_stu : public rclcpp::Node
{
private:
    int age = 0;
    rclcpp::Publisher<base_interface::msg::Student>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;

    //回调函数
    void on_timer()
    {
        auto message = base_interface::msg::Student();
        message.name = "lihua";
        message.age = age++;
        message.height = 2.2;
        RCLCPP_INFO(this->get_logger(),"服务端发布的消息： (%s,%d,%.2f)",message.name.c_str(),message.age,message.height);
        publisher_->publish(message);
    }


public:
    Talker_stu():Node("stu_talker_node_cpp")
    {
        RCLCPP_INFO(this->get_logger(),"消息发布方创建");
        publisher_ = this->create_publisher<base_interface::msg::Student>("chatter_stu",10);
        timer_ = this->create_wall_timer(500ms,bind(&Talker_stu::on_timer,this));
    }
};



int main(int argc,char const* argv[])
{
	rclcpp::init(argc,argv);
	rclcpp::spin(make_shared<Talker_stu>());  //回旋函数，代码执行到这一段将调用callback
  	rclcpp::shutdown();
  	return 0;
}