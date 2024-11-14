# roscar_ws
ROS话题通信初探——基于NMPC的无人车定点控制

# 0 项目结构  
src文件夹共包含三个功能包：  
car_model： 用于构建小车模型，创建小车节点test_car_model  
myplot：    用于可视化小车运行状态，创建绘图节点test_plot  
controller：用于构建nmpc控制器，创建节点test_nmpc  

# 1 项目依赖  
ros-noetic 
eigen3         （用于矩阵运算）  
casadi3.6.3    （linux，C++版本，用于求解NLP问题）  
matplotlibcpp  （用于绘图，由于调用的是python的绘图，因此需要安装python和相应的python绘图库）  

# 2 项目构建  
拷贝代码到本地文件夹：         git clone https://github.com/quyinsong/roscar_ws.git  
进入roscar_ws文件夹：        cd roscar_ws
在roscar_ws文件夹下运行：     catkin_make  

构建可能遇到的问题：

## 找不到自定义消息头文件，比如car_model/states.h，car_model/controls.h  

解决办法：打开car_model/CMakeList.txt文件,注释  

add_executable(test_pub ./src/test_pub.cpp)\
target_link_libraries(test_pub ${catkin_LIBRARIES})\
add_executable(test_car_model ./src/test_car_model.cpp ./src/car_model.cpp)\
target_link_libraries(test_car_model ${catkin_LIBRARIES})

打开controller文件夹，进入controller/CMakeList.txt文件，注释：

add_executable(test_nmpc ./src/test_nmpc.cpp ./src/nmpc1.cpp)\
target_link_libraries(test_nmpc ${catkin_LIBRARIES})\
target_link_libraries(test_nmpc /usr/local/lib/libcasadi.so.3.7) 

打开myplot文件夹，进入myplot/CMakeList.txt文件，注释

add_executable(test_plot ./src/test_plot.cpp ./src/comfun.cpp)\
target_link_libraries(test_plot ${catkin_LIBRARIES})\
target_include_directories(test_plot PRIVATE ${PYTHON2_INCLUDE_DIRS})\
target_link_libraries(test_plot ${PYTHON_LIBRARIES})

按照上述流程注释完成以后，执行catkin_make，编译生成msg头文件\
然后将上述注释取消，再执行catkin_make，即可编译成功\

## 找不到casadi头文件
自行安装casadi，参考https://blog.csdn.net/qq_41701758/article/details/131527719?spm=1001.2014.3001.5501

# 找不到matplotlibcpp头文件
git clone https://github.com/lava/matplotlib-cpp\
cp matplotlib-cpp/matplotlibcpp.h /usr/local/include/\

# 3 配置环境变量  
把当前工作空间的环境变量设置到bash中并source bashrc文件使其生效:  
echo "source ~/roscar_ws/devel/setup.bash" >> ~/.bashrc  
source ~/.bashrc  

# 4 运行  
首先在一个终端运行roscore  
然后另外分别打开三个终端分别输入如下指令  
rosrun car_model test_car_model  
rosrun myplot test_plot  
rosrun controller test_nmpc  

![image](https://github.com/user-attachments/assets/6e0866f9-c15c-4d77-b671-bf94488d563e)

![image](https://github.com/user-attachments/assets/ce8f129d-fe8b-486d-be44-6b80cb15d268)

注：用的是车的动力学模型，为了省事就直接用无人艇的几何模型绘图了

# 5 算法参数修改  
NMPC参数：在nmpc1.cpp中可修改惩罚矩阵Q和R的数值，m_Q和m_R  
设定期望点：在test_nmpc.cpp中可修改期望到达的位置，desired_states  

# 6 本人联系方式  
***

