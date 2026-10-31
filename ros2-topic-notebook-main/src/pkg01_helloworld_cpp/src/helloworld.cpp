#include "rclcpp/rclcpp.hpp"
using namespace std;

// int main(int argc, char ** argv)
// {
//   //初始化 ros2
//   rclcpp::init(argc,argv);
//   //创建节点
//   auto node = rclcpp::Node::make_shared("helloworld_node");
//   //输出文本
//   RCLCPP_INFO(node->get_logger(),"hello world");
//   //释放资源
//   rclcpp::shutdown();
//   return 0;
// }


//先使用初始化列创建节点再进行节点行为
class mynode : public rclcpp::Node
{
public:
	mynode():Node("helloworld_node_cpp") //定义节点名称
	{
		RCLCPP_INFO(this->get_logger(),"helloworld"); //节点行为
	}
};

int main(int argc, char const* argv[])
{
	//初始化
	rclcpp::init(argc,argv);
	//实例化自定义节点类
	auto node = make_shared<mynode>();
	//释放资源
	rclcpp::shutdown();

	return 0;
}