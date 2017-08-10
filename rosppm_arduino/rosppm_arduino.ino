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
#include <rosppm/ppm_io.h>

//Timer Initialization
#define timer_correction_factor 1.00                        //timer correction factor. This is needed if your arduino is too fast or slow, like mine. :(
#define timer_framelength 22000 * timer_correction_factor   //Maximum framelength in counter ticks
#define timer_pause 300 * timer_correction_factor           //Pause between pluses in counter ticks

// Pin Definitions
#define ppmout_PIN 10 // PPM output
#define ppmin_PIN 5 //PPM input
#define number_of_outputs 8 //Number of Outputs

#define mode_ppmout 1
#define mode_ppmin 0

//Timer variables
int timer_accumulator = 0;         //accumulator. Used to calculate the frame padding
int timer_ptr = 0;                 //timer array pointer

int pulses[number_of_outputs];
int in_pulses[number_of_outputs];
int buff_pulses[number_of_outputs];

float cmd_val[number_of_outputs];
float read_val[number_of_outputs];
float read_fval[number_of_outputs];

int count=0;//loopcount
int mode[1];

//ROS subscriber Callbacks
void set_ppm_Callback(const rosppm::ppm_io& msg){
  
  cmd_val[0]=msg.a;
  cmd_val[1]=msg.b;
  cmd_val[2]=msg.c;
  cmd_val[3]=msg.d;
  cmd_val[4]=msg.e;
  cmd_val[5]=msg.f;
  cmd_val[6]=msg.h;
  cmd_val[7]=msg.i;
  
}

ros::NodeHandle nh;

rosppm::ppm_io msg_read_ppm;
std_msgs::Float32 stat_msg;

ros::Subscriber<rosppm::ppm_io> sub_set_ppm("/rosppm_arduino/set_ppm", set_ppm_Callback);
ros::Publisher pub_read_ppm("/rosppm_arduino/read_ppm", &msg_read_ppm);
  
void setup()
{
  // ROS Configurations
  /// Initialize topics
  nh.initNode();
  nh.advertise(pub_read_ppm);
  nh.subscribe(sub_set_ppm);
  
  while(!nh.connected()){    nh.spinOnce();  }
  /// Get parameters
  if(! nh.getParam("/rosppm/mode", mode, 2)){
    mode[0] = 0;
  }
    
  // Hardware settings
  /// Set Pinmodes
  pinMode(ppmout_PIN, OUTPUT);
  pinMode(ppmin_PIN, INPUT);
  pinMode(13, OUTPUT); //status LED
  
  //Serial.begin(115200); // Initialize Serial
  // Setup Timer for ppm signal generation
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
  read_ppm();
  
  //Encode Read ppm values
  msg_read_ppm.a = read_val[1];
  msg_read_ppm.b = read_val[2];
  msg_read_ppm.c = read_val[3];
  msg_read_ppm.d = read_val[4];
  msg_read_ppm.e = read_val[5];
  msg_read_ppm.f = read_val[6];
  
  //Publish read ppm values
  pub_read_ppm.publish(&msg_read_ppm);
  
  timer_loopcount(); //Counter for handshake
  nh.spinOnce();
  
  delay(10);
   
}
