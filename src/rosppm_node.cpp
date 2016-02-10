#include <ros/ros.h>
#include <std_msgs/String.h> 
#include <stdio.h>
#include "sensor_msgs/Joy.h"
#include "std_msgs/Int16MultiArray.h"

#define loopRate 100

float set_axes[9];
int raw_set_axes[9];
int raw_read_axes[9];
float read_axes[9];

int num_Channels;

void set_channels_Callback(const sensor_msgs::Joy msg){
	
	for(int i=0; i<num_Channels; i++){
	 set_axes[i] = msg.axes.[i];
	}

}


void raw_read_channels_Callback(const std_msgs::Int16MultiArray msg){
	
	for(int i=0; i<num_Channels; i++){
	 	raw_read_axes[i] = msg.data.[i];
	}


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

int main(int argc, char **argv)
{
   ros::init(argc, argv, "rosppm_node");
   ros::NodeHandle n;
   
   //rosppm interface using Joy message
   ros::Publisher pub_read_channels = n.advertise<sensor_msgs::Joy>("/ppm/read_channels",loopRate);
   ros::Subscriber sub_set_channels = n.subscribe<sensor_msgs::Joy>("/ppm/set_channels", loopRate, set_channels_Callback);
   
   //Raw message for rosppm raw message
   ros::Publisher pub_raw_set_channels =n.advertise<std_msgs::Int16MultiArray>("/rosppm/raw_set_channels", loopRate);
   ros::Subscriber sub_raw_read_channels =n.subscribe<std_msgs::Int16MultiArray>("/rosppm/raw_read_channels", loopRate, raw_read_channels_Callback);
   
   ros::Rate loop_rate(loopRate);
   ros::spinOnce();

   sensor_msgs::Joy read_channels;
   std_msgs::Int16MultiArray raw_set_channels;

   int count = 1;

   n.param("rosppm/number_of_channels", num_Channels, 9);
		
   while(ros::ok()){
	
	   encode_Ppm();
	   encode_Joy();

	//Encode read channel message
       read_channels.header.stamp = ros::Time::now();
       read_channels.header.seq=count;
       read_channels.header.frame_id = 1;
	   for(int i=0; i<num_Channels; i++){
			read_channels.axes.[i] = read_axes[i];
	   }
    //Encode set channels to raw messages
	   for(int i=0; i<num_Channels; i++){
			raw_set_channels.data.[i] = raw_set_axes[i];
	   }
       
	   pub_read_channels.publish(read_channels); //Subscirbe set channel values
       pub_raw_set_channels.publish(raw_set_channels); //

	   ros::spinOnce();
       count++;
       loop_rate.sleep();
   }  
   return 0;
}
