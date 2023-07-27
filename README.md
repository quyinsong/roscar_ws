# roscar_ws
ROS话题通信初探——基于NMPC的无人车定点控制

0 项目结构
src文件夹共包含三个功能包：
car_model： 用于构建小车模型，创建小车节点test_car_model
myplot：    用于可视化小车运行状态，创建绘图节点test_plot
controller：用于构建nmpc控制器，创建节点test_nmpc

1 项目依赖
ros-noetic
eigen3         （用于矩阵运算）
casadi3.6.3    （linux，C++版本，用于求解NLP问题）
matplotlibcpp  （用于绘图，由于调用的是python的绘图，因此需要安装python和相应的python绘图库）

2 项目构建
在主目录下创建文件夹roscar_ws：mkdir roscar_ws
拷贝代码到本地文件夹：         git clone https://github.com/quyinsong/roscar_ws.git
在roscar_ws文件夹下运行：     catkin_make

3 配置环境变量
把当前工作空间的环境变量设置到bash中并source bashrc文件使其生效:
echo "source ~/roscar_ws/devel/setup.bash" >> ~/.bashrc
source ~/.bashrc

4 运行
首先在一个终端运行roscore
然后另外分别打开三个终端分别输入如下指令
rosrun car_model test_car_model
rosrun myplot test_plot
rosrun controller test_nmpc

5 算法参数修改
NMPC参数：在nmpc1.cpp中可修改惩罚矩阵Q和R的数值，m_Q和m_R
设定期望点：在test_nmpc.cpp中可修改期望到达的位置，desired_states

6 本人联系方式
qu13298110549@163.com


