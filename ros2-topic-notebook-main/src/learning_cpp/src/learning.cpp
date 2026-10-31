#include "rclcpp/rclcpp.hpp"

int main(int argc,char const *argv[])
{
	//初始化ros2
	rclcpp::init(argc,argv);

	//创建节点指针
	auto node = rclcpp::Node::make_shared("helloworld_node_cpp");

	//输出日志
	RCLCPP_INFO(node->get_logger(),"hello.....");

	//释放资源
	rclcpp::shutdown();


	return 0;
}