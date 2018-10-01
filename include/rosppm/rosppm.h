//
// Created by jalim on 01.10.18.
//

#ifndef ROSPPM_ROSPPM_H
#define ROSPPM_ROSPPM_H

#include <ros/ros.h>
#include <sensor_msgs/Joy.h>

using namespace std;

class rosppm
{
  private:
    ros::NodeHandle nh_;
    ros::NodeHandle nh_private_;
    ros::Publisher pub_read_channels;
    ros::Publisher setppmPub_;
    ros::Subscriber setppmSub_;
    ros::Subscriber readppmSub_;
    ros::Timer cmdloop_timer_;
    sensor_msgs::Joy joy_read_channels;
    sensor_msgs::Joy joy_set_channels;
//    rosppm::ppm_io msg_ppm_set;
//    rosppm::ppm_io msg_ppm_read;
    float joy_set_axes[9];
    float read_axes[9];
    int numChannels_;

public:
    rosppm(const ros::NodeHandle& nh, const ros::NodeHandle& nh_private);
    virtual ~ rosppm();
    void loopCallback(const ros::TimerEvent& envent);
    void joychannelCallback(sensor_msgs::Joy msg);
    void readppmCallback(sensor_msgs::Joy msg);
    void joysetchannelsCallback(const sensor_msgs::Joy msg);

};

#endif //ROSPPM_ROSPPM_H
