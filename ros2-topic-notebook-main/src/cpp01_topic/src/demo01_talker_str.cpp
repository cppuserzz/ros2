#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
using namespace std;

//自定义节点
class Talker : public rclcpp::Node
{
private:
	int count_ = 0;
	rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
	rclcpp::TimerBase::SharedPtr timer_;

	//通过回调函数来发布信息
	void on_timer()
	{
		//通过发布对象来发布消息
		auto message = std_msgs::msg::String();
		message.data = "hello world " + to_string(count_++);
		//日志输出服务端发布的消息
		RCLCPP_INFO(this->get_logger(),"服务端发布的消息:%s",message.data.c_str());  //把c++风格字符串转换成c风格字符串格式化打印
		// 发布消息
		publisher_->publish(message);
		// count_++;
	}
public:
	Talker():Node("talker_node_cpp")
	{
		RCLCPP_INFO(this->get_logger(),"发布节点创建");
		//创建消息发布方,返回一个发布对象
		publisher_ = this->create_publisher<std_msgs::msg::String>("chatter",10); //前一个是话题名称 ,第二个参数是队列深度
		//创建定时器，返回一个定时器对象指针
		timer_ = this->create_wall_timer(1s,bind(&Talker::on_timer , this)); //前一个是定时时间，后面 回调函数 绑定函数（this调用当前类下的on_timer函数）
		//隔固定时间调用一次回调函数
	}
};



int main(int argc,char const* argv[])
{
	rclcpp::init(argc,argv);
	rclcpp::spin(make_shared<Talker>());  //回旋函数，代码执行到这一段将调用callback
  	rclcpp::shutdown();
  	return 0;
}