//
// Created by jalim on 01.10.18.
//
#include "rosppm/rosppm.h"

#define loopRate 100

rosppm::rosppm(const ros::NodeHandle& nh, const ros::NodeHandle& nh_private):
  nh_(nh),
  nh_private_(nh_private) {

  //rosppm interface using Joy message
  cmdloop_timer_ = nh_.createTimer(ros::Duration(0.01), &rosppm::loopCallback, this); // Define timer for constant loop rate
  pub_read_channels = nh_.advertise<sensor_msgs::Joy>("/rosppm_interface/joy_read_channels",loopRate);
  setppmPub_ = nh_.advertise<rosppm::ppm_io>("/rosppm_arduino/set_ppm", loopRate);
  setppmSub_ = nh_.subscribe("/rosppm_interface/joy_set_channels", 1, &rosppm::joychannelCallback, this, ros::TransportHints().tcpNoDelay());
  readppmSub_ = nh_.subscribe("/rosppm_arduino/read_ppm", 1, &rosppm::readppmCallback, this, ros::TransportHints().tcpNoDelay());

  nh_.param("rosppm/number_of_channels", numChannels_, 9);
}
rosppm::~rosppm() {
  //Destructor
}

void rosppm::loopCallback(const ros::TimerEvent& event){
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
//  pub_read_channels.publish(joy_read_channels); //Subscirbe set channel values
//  pub_set_ppm.publish(msg_ppm_set);
}

void rosppm::joychannelCallback(sensor_msgs::Joy msg){
  //Set channel values from joystick input

}

void rosppm::readppmCallback(sensor_msgs::Joy msg){
  //Read PPM values from transmitter value

}

void rosppm::joysetchannelsCallback(const sensor_msgs::Joy msg){

  for(int i=0; i<numChannels_; i++){
    joy_set_axes[i] = msg.axes[i];
  }
}

void read_ppm_Callback(const rosppm::ppm_io msg){

}