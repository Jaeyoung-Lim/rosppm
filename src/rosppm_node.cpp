#include "rosppm/rosppm.h"

int main(int argc, char **argv) {

  ros::init(argc, argv, "rosppm_node");
  ros::NodeHandle nh("");
  ros::NodeHandle nh_private("~");

  rosppm ppm_io(nh, nh_private);
  ros::spin();
  return 0;

}

