#include <ros/ros.h>
#include <std_msgs/String.h> 
#include <stdio.h>
#include "sensor_msgs/Joy.h"

#define loopRate 100

float set_axes[9];
int raw_axes[9];


void set_channels_Callback(const sensor_msgss::Joy sub_msg){
	set_axes[0] = sub_msg.axes[0];
	set_axes[1] = sub_msg.axes[1];
	set_axes[2] = sub_msg.axes[3];
	set_axes[3] = sub_msg.axes[4];
	set_axes[4] = sub_msg.axes[5];
	set_axes[5] = sub_msg.axes[6];
	set_axes[6] = sub_msg.axes[7];
	set_axes[7] = sub_msg.axes[8];
	set_axes[8] = sub_msg.axes[9];

}


void raw_read_channels_Callback(const std_msgs::Int32MultiArray sub_msg){


}

void encode_Joy(){
	 for(int i=0; i<9; i++){
		  raw_axes = (int) (set_axes[i]+1.0);

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
   ros::Subsriber pub_raw_set_channels =n.advertise<std_msgs::Int32MultiArray>("/rosppm/raw_read_channels", loopRate, raw_read_channels_Callback);
   
   ros::Rate loop_rate(loopRate);
   ros::spinOnce();

   sensor_msgs::Joy read_channels;
   sensor_msgs::Int32MultiArray raw_set_channels;

   int count = 1;
		
   while(ros::ok()){
	
	   encode_Joy();	
	//Encode set raw channel message
	   set_channels.header

	//Encode read channel message
       read_channels.header.stamp = ros::Time::now();
       read_channels.header.seq=count;
       read_channels.header.frame_id = 1;
       read_channels.axes[0] = set_axes[0];
       read_channels.axes[1] = set_axes[1];
       read_channels.axes[2] = set_axes[2];
       read_channels.axes[3] = set_axes[3];
       read_channels.axes[4] = set_axes[4];
       read_channels.axes[5] = set_axes[5];
       read_channels.axes[6] = set_axes[6];
       read_channels.axes[7] = set_axes[7];
       read_channels.axes[8] = set_axes[8];
       
       pub_read_channels.publish(read_channels);
       ros::spinOnce();
       count++;
       loop_rate.sleep();
   }
   
      
   return 0;
}
