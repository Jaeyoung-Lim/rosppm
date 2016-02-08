#include <ros/ros.h>
#include <std_msgs/String.h> 
#include <stdio.h>
#include "sensor_msgs/Joy.h"

#define loopRate 100

float val_axes[]
void set_channels_Callback(const sensor_msgss::Joy sub_msg){
	val_axes[0] = sub_msg.axes[0];


}

int main(int argc, char **argv)
{
   ros::init(argc, argv, "pub_setpoints");
   ros::NodeHandle n;
   
   //rosppm interface using Joy message
   ros::Publisher pub_read_channels = n.advertise<sensor_msgs::Joy>("/rosppm/read_channels",loopRate);
   ros::Subscriber sub_set_channels = n.advertise<sensor_msgs::Joy>("/rosppm/set_channels", loopRate, set_channels_Callback);
   
   //Raw message for rosppm raw message
   ros::Publisher pub_raw_set_channels =n.advertise<std_msgs::Int32MultiArray>("/rosppm/raw_set_channels", loopRate);
   ros::Subsriber pub_raw_set_channels =n.advertise<std_msgs::Int32MultiArray>("/rosppm/raw_read_channels", loopRate);
   
   ros::Rate loop_rate(loopRate);
   ros::spinOnce();

   sensor_msgs::Joy read_channels;
   sensor_msgs::Int32MultiArray raw_set_channels;

   int count = 1;
		
   while(ros::ok()){
	//Encode set raw channel message
	   set_channels.header

	//Encode read channel message
       read_channels.header.stamp = ros::Time::now();
       read_channels.header.seq=count;
       read_channels.header.frame_id = 1;
       read_channels.axes[0] = 0.0;//0.001*some_object.position_x;
       read_channels.axes[1] = 0.0;//0.001*some_object.position_x;
       read_channels.axes[2] = 0.0;//0.001*some_object.position_x;
       read_channels.axes[3] = 0.0;//0.001*some_object.position_x;
       read_channels.axes[4] = 0.0;//0.001*some_object.position_x;
       read_channels.axes[5] = 0.0;//0.001*some_object.position_x;
       read_channels.axes[6] = 0.0;//0.001*some_object.position_x;
       read_channels.axes[7] = 0.0;//0.001*some_object.position_x;
       read_channels.axes[8] = 0.0;//0.001*some_object.position_x;
       
       pub_read_channels.publish(read_channels);
       ros::spinOnce();
       count++;
       loop_rate.sleep();
   }
   
      
   return 0;
}
