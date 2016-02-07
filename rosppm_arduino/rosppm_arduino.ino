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
#include <std_msgs/Float32MultiArray.h>

//Timer Initialization
#define timer_correction_factor 1.00                        //timer correction factor. This is needed if your arduino is too fast or slow, like mine. :(
#define timer_framelength 22000 * timer_correction_factor   //Maximum framelength in counter ticks
#define timer_pause 300 * timer_correction_factor           //Pause between pluses in counter ticks
// Pin Definitions
#define ppmout_PIN 10 // PPM output

//Mode ID
//#define mode_trim 0
//#define mode_serial 1
int mode=0;
float cmd_val[];

//Timer variables
int timer_accumulator = 0;         //accumulator. Used to calculate the frame padding
int timer_ptr = 0;                 //timer array pointer
int pulses[8];
int number_of_outputs =8;

int count=0;

void cmd_Callback(const std_msgs::Float32MultiArray& cmd_msg){
  cmd_val[0]=cmd_msg.data[0];
  cmd_val[1]=cmd_msg.data[1];
  cmd_val[2]=cmd_msg.data[2];
  cmd_val[3]=cmd_msg.data[3];
}


ros::NodeHandle  nh;
ros::Subscriber<std_msgs::Float32MultiArray> sub("/rosppm/cmd_Ch", cmd_Callback);
ros::Publisher chatter("/rosppm/read_Ch", &str_msg);

void setup()
{
s  nh.initNode();
  nh.advertise(chatter);
  nh.subscribe(sub);
  
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

  //chatter.publish( &str_msg );
  ppm_command(mode); //Set pulse values for PPM signal
  timer_loopcount(); //Counter for handshake
  
  nh.spinOnce();
  
  delay(18);
   
}
