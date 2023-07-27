#include <ros/ros.h>
#include "car_model/states.h"
#include "car_model/controls.h"
#include "nmpc1.h"


/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */

//由于回调函数不能返回数值，若想处理回调函数接收的话题消息，需要定义如下Listener类，
//利用类中成员来处理接收到的消息
class Listener
{
public:
    Eigen::Matrix<float,3,1> current_states;

public:
    Listener();
    ~Listener();
    void callback(const car_model::states::ConstPtr& msg);
};

Listener::Listener()
{

}

Listener::~Listener()
{

}

void Listener::callback(const car_model::states::ConstPtr& msg)
{
    // ROS_INFO("I heard states: [%f, %f, %f]", msg->x, msg->y, msg->theta);

    current_states<<msg->x,msg->y,msg->theta;

    // ROS_INFO("current states: [%f, %f, %f]", pos[0], pos[1], psi);
}

//主函数
int main(int argc, char **argv)
{
    //初始化ros节点
    ros::init(argc, argv, "test_nmpc");

    ros::NodeHandle n;

    //创建NMPC控制器
    int predict_step = 10;
    float sample_time = 0.02;
    NMPC1 nmpc1(predict_step, sample_time);

    //设定期望最终位置与控制量
    Eigen::Vector3f desired_states;
    Eigen::Vector2f desired_controls;
    desired_states<< 20,20,0;
    desired_controls<< 0,0;

    //创建监听对象
    Listener mlistener;

    ros::Subscriber sub = n.subscribe("/car_states",100,&Listener::callback,&mlistener);

    //创建发布对象
    ros::Publisher pub =n.advertise<car_model::controls>("/nmpc_controls",100);

    // 设置循环的频率
    ros::Rate loop_rate(50);

    while(ros::ok())
    {
        //循环回调函数
        ros::spinOnce();
        
        //调用nmpc求解
        nmpc1.opti_solution(mlistener.current_states,desired_states,desired_controls);
        //获取控制量
        Eigen::Vector2f nmpc_controls = nmpc1.get_controls();

        //发布求解得到的控制量
        car_model::controls pub_msg;
        pub_msg.v = nmpc_controls[0];
        pub_msg.omega = nmpc_controls[1];

        pub.publish(pub_msg);

        //休眠
        loop_rate.sleep();
    }
 

  return 0;
}