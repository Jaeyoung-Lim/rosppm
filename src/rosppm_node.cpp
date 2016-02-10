#include <ros/ros.h>
#include <std_msgs/String.h> 
#include <stdio.h>
#include "sensor_msgs/Joy.h"
#include "std_msgs/Float32.h"

#define loopRate 100

float set_axes[9];
int raw_set_axes[9];
int raw_read_axes[9];
float read_axes[9];

int num_Channels;

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
/*
void encode_Ppm(){
	 
	 for(int i=0; i<num_Channels; i++){
		 raw_set_axes[i] = (int) (set_axes[i]*512.0+512.0);
	 }

}
*/
void encode_Joy(){
	int f_raw_read_axes[9];
	for(int i=0; i<num_Channels; i++){
		 
		 f_raw_read_axes[i]= (float) raw_read_axes[i];
		 raw_read_axes[i] = f_raw_read_axes[i]/512.0-1.0;
	}
}

int main(int argc, char **argv)
{
   ros::init(argc, argv, "rosppm_node");
   ros::NodeHandle n;
   
   //rosppm interface using Joy message
   ros::Publisher pub_read_channels = n.advertise<sensor_msgs::Joy>("/ppm/read_channels",loopRate);
   ros::Subscriber sub_set_channels = n.subscribe<sensor_msgs::Joy>("/ppm/set_channels", loopRate, set_channels_Callback);
   
   //Raw message for rosppm raw message
   ros::Publisher pub_raw_set_ch1 =n.advertise<std_msgs::Float32>("/rosppm/raw_set_ch1", loopRate);
   ros::Publisher pub_raw_set_ch2 =n.advertise<std_msgs::Float32>("/rosppm/raw_set_ch2", loopRate);
   ros::Publisher pub_raw_set_ch3 =n.advertise<std_msgs::Float32>("/rosppm/raw_set_ch3", loopRate);
   ros::Publisher pub_raw_set_ch4 =n.advertise<std_msgs::Float32>("/rosppm/raw_set_ch4", loopRate);

   ros::Subscriber sub_raw_read_ch1 =n.subscribe<std_msgs::Float32>("/rosppm/raw_read_ch1", loopRate, raw_read_ch1_Callback);
   ros::Subscriber sub_raw_read_ch2 =n.subscribe<std_msgs::Float32>("/rosppm/raw_read_ch2", loopRate, raw_read_ch2_Callback);
   ros::Subscriber sub_raw_read_ch3 =n.subscribe<std_msgs::Float32>("/rosppm/raw_read_ch3", loopRate, raw_read_ch3_Callback);
   ros::Subscriber sub_raw_read_ch4 =n.subscribe<std_msgs::Float32>("/rosppm/raw_read_ch4", loopRate, raw_read_ch4_Callback);
   
   ros::Rate loop_rate(loopRate);
   ros::spinOnce();

   sensor_msgs::Joy read_channels;
   std_msgs::Float32 raw_set_ch1;
   std_msgs::Float32 raw_set_ch2;
   std_msgs::Float32 raw_set_ch3;
   std_msgs::Float32 raw_set_ch4;
   
   int count = 1;

   n.param("rosppm/number_of_channels", num_Channels, 9);   
		
   while(ros::ok()){

	//Encode read channel message
       read_channels.header.stamp = ros::Time::now();
       read_channels.header.seq=count;
       read_channels.header.frame_id = 1;
	   read_channels.axes.resize(9);
	   for(int i=0; i<num_Channels; i++){
			read_channels.axes[i] = read_axes[i];
	   }
	   
    //Encode set channels to raw messages
	   
	   
	  
	   raw_set_ch1.data = raw_set_axes[0];
	   raw_set_ch2.data = raw_set_axes[1];
	   raw_set_ch3.data = raw_set_axes[2];
	   raw_set_ch4.data = raw_set_axes[3];
	   
       
	   pub_read_channels.publish(read_channels); //Subscirbe set channel values
       pub_raw_set_ch1.publish(raw_set_ch1); //
       pub_raw_set_ch2.publish(raw_set_ch2); //
       pub_raw_set_ch3.publish(raw_set_ch3); //
       pub_raw_set_ch4.publish(raw_set_ch4); //

	   ros::spinOnce();
       count++;
       loop_rate.sleep();
   }  
   return 0;
}
