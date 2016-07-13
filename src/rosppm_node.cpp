#include <ros/ros.h>
#include <std_msgs/String.h> 
#include <stdio.h>
#include "sensor_msgs/Joy.h"
#include "std_msgs/Float32.h"
#include "rosppm/ppm_io.h"
#define loopRate 100

float joy_set_axes[9];
float read_axes[9];

int num_Channels;

void joy_set_channels_Callback(const sensor_msgs::Joy msg){
	
	for(int i=0; i<num_Channels; i++){
	 joy_set_axes[i] = msg.axes[i];
	}
}

void read_ppm_Callback(const rosppm::ppm_io msg){

}

int main(int argc, char **argv)
{
   ros::init(argc, argv, "rosppm_node");
   ros::NodeHandle n;
   
   //rosppm interface using Joy message
   ros::Publisher pub_read_channels = n.advertise<sensor_msgs::Joy>("/rosppm_interface/joy_read_channels",loopRate);
   ros::Subscriber sub_set_channels = n.subscribe<sensor_msgs::Joy>("/rosppm_interface/joy_set_channels", loopRate, joy_set_channels_Callback);
   //PPM command message
   ros::Publisher pub_set_ppm = n.advertise<rosppm::ppm_io>("/rosppm_arduino/set_ppm", loopRate);
   ros::Subscriber sub_read_ppm = n.subscribe<rosppm::ppm_io>("/rosppm_arduino/read_ppm", loopRate, read_ppm_Callback);
   
   ros::Rate loop_rate(loopRate);
   ros::spinOnce();

   sensor_msgs::Joy joy_read_channels;
   sensor_msgs::Joy joy_set_channels;
   rosppm::ppm_io msg_ppm_set;
   rosppm::ppm_io msg_ppm_read;

   int count = 1;

   n.param("rosppm/number_of_channels", num_Channels, 9);
   //n.param("rosppm/mode", mode, 0);
		
   while(ros::ok()){

		//Encode read channel message
		
		msg_ppm_set.a = joy_set_axes[0];
		msg_ppm_set.b = joy_set_axes[1];
		msg_ppm_set.c = joy_set_axes[2];
		msg_ppm_set.d = joy_set_axes[3];
		msg_ppm_set.e = joy_set_axes[4];
		msg_ppm_set.f = joy_set_axes[5];
		msg_ppm_set.g = joy_set_axes[6];
		msg_ppm_set.h = joy_set_axes[7];
		msg_ppm_set.i = joy_set_axes[8];

		//Publish messages      
		pub_read_channels.publish(joy_read_channels); //Subscirbe set channel values
		pub_set_ppm.publish(msg_ppm_set);
		ros::spinOnce();
		count++;
		loop_rate.sleep();
   }  
   return 0;
}
