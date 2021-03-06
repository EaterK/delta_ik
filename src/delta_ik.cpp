#include <ros/ros.h>
// #include <std_msgs/Int32MultiArray.h>
#include <std_msgs/Float32MultiArray.h>

// #include <sensor_msgs/Joy.h>

#include "../include/calc.h"
#include "../include/const.h"

#include <sstream>

#define DELTA_IK_HZ 60

std_msgs::Float32MultiArray fPub_val;
float calc_pos[3]={0};  //calculating position

bool ik_available=false;

void callback(const std_msgs::Float32MultiArray& msg)
{
    for(int i=0;i<3;i++)
    {
        ROS_INFO("input[%d]=%f",i,msg.data[i]);
    }
    if(-1 == delta_calcInverse(msg.data[0],msg.data[1],msg.data[2],calc_pos[0],calc_pos[1],calc_pos[2]))
    {
        ROS_INFO("IK(%f,%f,%f) has NO SOLUTION !!",msg.data[0],msg.data[1],msg.data[2]);
        ik_available = false;
    }else
    {
        ROS_INFO("IK(%f,%f,%f) has a SOLUTION (%f,%f,%f)",msg.data[0],msg.data[1],msg.data[2],calc_pos[0],calc_pos[1],calc_pos[2]);
        ik_available = true;
    }
    return;
}

int main(int argc, char** argv)
{
    ros::init(argc,argv,"delta_ik_node");
    ros::NodeHandle nh,nh2;

    // ros::Publisher ik_pub = nh.advertise<std_msgs::Int32MultiArray>("pos_cmd", 1000);
    ros::Publisher ik_pub = nh.advertise<std_msgs::Float32MultiArray>("servo_pos_cmd", 1000);
    ros::Rate loop_rate(DELTA_IK_HZ);

    ros::Subscriber cmd_sub = nh2.subscribe("ee_pos",1000, callback);

    // for(int i=0;i<3;i++)iPub_val.data[i]=0;
    fPub_val.data.resize(3);
    for(int i=0;i<3;i++)fPub_val.data[i]=0;

    while(ros::ok())
    {
        if(ik_available)
        {
            for(int i=0;i<3;i++)
            {
                fPub_val.data[i]=calc_pos[i];
            }
            ik_available=false;
        }

        ik_pub.publish(fPub_val);
        ROS_INFO("theta1=%f, theta2=%f, theta3=%f",fPub_val.data[0],fPub_val.data[1],fPub_val.data[2]);

        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}
