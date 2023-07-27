#include <iostream>
#include <ros/ros.h>
#include <std_msgs/String.h>

int main(int argc, char **argv)
{
    // ROS节点初始化
    ros::init(argc, argv, "test_pub");
    // 创建节点句柄
    ros::NodeHandle n;
    // 创建一个Publisher，发布名为/hello的topic，消息类型为std_msgs::String，队列长度100
    ros::Publisher msg_pub = n.advertise<std_msgs::String>("/hello", 100);
    // 设置循环的频率
    ros::Rate loop_rate(1);
    int count = 0;
    while (ros::ok())
    {
        // 初始化std_msgs类型的消息
        std::string ss;
        ss = "hello "+std::to_string(count);

    	std_msgs::String msg;
        msg.data = ss;

        msg_pub.publish(msg);

        //打印消息
        ROS_INFO("%s", msg.data.c_str());

        ros::spinOnce();
        loop_rate.sleep();
        ++count;

    }

    return 0;
}