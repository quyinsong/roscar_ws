#include <ros/ros.h>
#include "car_model.h"        //小车模型头文件
#include "car_model/states.h" //自定义消息头文件
#include "car_model/controls.h"

/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */

//由于回调函数不能返回数值，若想处理回调函数接收的话题消息，需要定义如下Listener类，
//利用类中成员来处理接收到的消息
class Listener
{
public:
    Eigen::Matrix<float,2,1> controller_controls;

public:
    Listener();
    ~Listener();
    void callback(const car_model::controls::ConstPtr& msg);
};

Listener::Listener()
{

}

Listener::~Listener()
{

}

void Listener::callback(const car_model::controls::ConstPtr& msg)
{
    // ROS_INFO("I heard states: [%f, %f, %f]", msg->x, msg->y, msg->theta);

    controller_controls<<msg->v,msg->omega;

    // ROS_INFO("current states: [%f, %f, %f]", pos[0], pos[1], psi);
}

int main(int argc, char **argv)
{
    //初始化ros节点
    ros::init(argc,argv,"test_car_model"); 
    ros::NodeHandle nh;
    // 创建一个Publisher，发布名为/hello的topic，消息类型为std_msgs::String，队列长度100
    ros::Publisher msg_pub = nh.advertise<car_model::states>("/car_states", 100);
    // 创建一个监听对象，接收控制器的控制指令
    Listener mlistener;
    ros::Subscriber msg_sub = nh.subscribe<car_model::controls>("/nmpc_controls",100,&Listener::callback,&mlistener);
    //初始化小车
    float sample_time = 0.02;     //采样时间，用来更新小车状态
    Eigen::Vector3f states;       //小车x,y,theta状态
    states<<0,0,0;
    Eigen::Vector2f controls;     //小车控制量
    controls<<1,0.05;
    Car car(sample_time, states); //创建小车
    // 设置循环的频率
    ros::Rate loop_rate(50);
    //开始仿真
    while(ros::ok())
    {
        //循环回调
        ros::spinOnce();
        //接收控制指令
        controls = mlistener.controller_controls;
        //无人艇
        car.state_update(controls);
        states = car.get_states();
        //发布无人艇状态
        car_model::states states_msg;
        states_msg.x = states[0];
        states_msg.y = states[1];
        states_msg.theta = states[2];
        msg_pub.publish(states_msg);

        //休眠延迟
        loop_rate.sleep();

    }

}