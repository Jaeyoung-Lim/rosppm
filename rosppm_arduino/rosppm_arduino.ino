/*
  USB2PPM Firmware
  This program receives commands for 4 channels from the PC via string and convert it into 9 channels of ppm signals to interface with the transmitter.
  Currently this code has been tested only on Turnigy 9X. Other transmitters may be compatible but may have volatage issues
  Version 1.0.0
  
  Jaeyoung Lim
*/
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <std_msgs/Float32.h>
#include "sensor_msgs/Joy.h"
//Timer Initialization
#define timer_correction_factor 1.00                        //timer correction factor. This is needed if your arduino is too fast or slow, like mine. :(
#define timer_framelength 22000 * timer_correction_factor   //Maximum framelength in counter ticks
#define timer_pause 300 * timer_correction_factor           //Pause between pluses in counter ticks
// Pin Definitions
#define ppmout_PIN 10 // PPM output
#define number_of_outputs 8

//Timer variables
int timer_accumulator = 0;         //accumulator. Used to calculate the frame padding
int timer_ptr = 0;                 //timer array pointer
int pulses[number_of_outputs];
float cmd_val[number_of_outputs];

int count=0;

void set_ch1_Callback(const std_msgs::Float32& msg){
  cmd_val[0]=msg.data;
}
void set_ch2_Callback(const std_msgs::Float32& msg){
  cmd_val[1]=msg.data;
}
void set_ch3_Callback(const std_msgs::Float32& msg){
  cmd_val[2]=msg.data;
}
void set_ch4_Callback(const std_msgs::Float32& msg){
  cmd_val[3]=msg.data;
}


ros::NodeHandle nh;
std_msgs::Float32 raw_read_ch1;
std_msgs::Float32 raw_read_ch2;
std_msgs::Float32 raw_read_ch3;
std_msgs::Float32 raw_read_ch4;

std_msgs::Float32 stat_msg;

ros::Subscriber<std_msgs::Float32> sub_set_ch1("/rosppm/raw_set_Ch1", set_ch1_Callback);
ros::Subscriber<std_msgs::Float32> sub_set_ch2("/rosppm/raw_set_Ch2", set_ch2_Callback);
ros::Subscriber<std_msgs::Float32> sub_set_ch3("/rosppm/raw_set_Ch3", set_ch3_Callback);
ros::Subscriber<std_msgs::Float32> sub_set_ch4("/rosppm/raw_set_Ch4", set_ch4_Callback);

ros::Publisher pub_read_ch1("/rosppm/raw_read_Ch1", &raw_read_ch1);
ros::Publisher pub_read_ch2("/rosppm/raw_read_Ch2", &raw_read_ch2);
ros::Publisher pub_read_ch3("/rosppm/raw_read_Ch3", &raw_read_ch3);
ros::Publisher pub_read_ch4("/rosppm/raw_read_Ch4", &raw_read_ch4);


void setup()
{
  nh.initNode();
  nh.advertise(pub_read_ch1);
  nh.advertise(pub_read_ch2);
  nh.advertise(pub_read_ch3);
  nh.advertise(pub_read_ch4);
  nh.subscribe(sub_set_ch1);
  nh.subscribe(sub_set_ch2);
  nh.subscribe(sub_set_ch3);
  nh.subscribe(sub_set_ch4);
  
  //Set Pinmodes
  pinMode(ppmout_PIN, OUTPUT);
  pinMode(13, OUTPUT);
  //Serial.begin(115200); // Initialize Serial
                      // Setup Timer
  TCCR1A = B00110001; // Compare register B used in mode '3'
  TCCR1B = B00010010; // WGM13 and CS11 set to 1
  TCCR1C = B00000000; // All set to 0
  TIMSK1 = B00000010; // Interrupt on compare B
  TIFR1  = B00000010; // Interrupt on compare B
  OCR1A = timer_framelength;
  OCR1B = timer_pause; 
  
}

void loop(){

  set_ppm(); //Set pulse values for PPM signal
  timer_loopcount(); //Counter for handshake
  
  pub_read_ch1.publish(&raw_read_ch1);
  pub_read_ch2.publish(&raw_read_ch1);
  pub_read_ch3.publish(&raw_read_ch1);
  pub_read_ch4.publish(&raw_read_ch1);
  
  nh.spinOnce();
  
  delay(10);
   
}
