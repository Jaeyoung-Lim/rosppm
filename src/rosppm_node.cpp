#include <ros/ros.h>
#include <std_msgs/String.h> 
#include <stdio.h>
#include "sensor_msgs/Joy.h"
#include "std_msgs/Float32.h"
#include "rosppm/ppm_io.h"
#define loopRate 100

float set_axes[9];
int raw_set_axes[9];
int raw_read_axes[9];
float read_axes[9];

int num_Channels;
/*
void set_channels_Callback(const sensor_msgs::Joy msg){
	
	for(int i=0; i<num_Channels; i++){
	 set_axes[i] = msg.axes[i];
	}
}


void raw_read_ch1_Callback(const std_msgs::Float32 msg){
	 	raw_read_axes[0] = msg.data;
}

void raw_read_ch2_Callback(const std_msgs::Float32 msg){
	 	raw_read_axes[1] = msg.data;
}

void raw_read_ch3_Callback(const std_msgs::Float32 msg){
	 	raw_read_axes[2] = msg.data;
}

void raw_read_ch4_Callback(const std_msgs::Float32 msg){
	 	raw_read_axes[3] = msg.data;
}

void encode_Ppm(){
	 
	 for(int i=0; i<num_Channels; i++){
		 raw_set_axes[i] = (int) (set_axes[i]*512.0+512.0);
	 }

}

void encode_Joy(){
	int f_raw_read_axes[9];
	for(int i=0; i<num_Channels; i++){
		 
		 f_raw_read_axes[i]= (float) raw_read_axes[i];
		 raw_read_axes[i] = f_raw_read_axes[i]/512.0-1.0;
	}
}
*/
int main(int argc, char **argv)
{
   ros::init(argc, argv, "rosppm_node");
   ros::NodeHandle n;
   
   //rosppm interface using Joy message
   ros::Publisher pub_cmd_ppm = n.advertise<rosppm::ppm_io>("/rosppm/cmd_ppm",loopRate);
   
   ros::Rate loop_rate(loopRate);
   ros::spinOnce();

   //sensor_msgs::Joy read_channels;
   //std_msgs::Float32 raw_set_ch1;
   
   int count = 1;

   n.param("rosppm/number_of_channels", num_Channels, 9);   
		
   while(ros::ok()){

	//Encode read channel message
    //Encode set channels to raw messages
	   
       


	   ros::spinOnce();
       count++;
       loop_rate.sleep();
   }  
   return 0;
}
