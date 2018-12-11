# rosppm

rosppm is a ROS package which enables ROS to interface with an mcu that generates ppm signal to interface with an RC transmitter.

## Features
- Transmit Channel values to the transmitter using the trainer port
- Receive stick values from the transmitter coming out of the trainer port
- Arm the autopilot using usb2ppm_ros (Work in progress)

## Hardware
Currently tested transmitters follow as below, but in principle will be compatible with most ppm compatible transmitters when followed proper wiring.

More instructions are presented in the following [link](https://404warehouse.net/2016/07/13/rosppm-ros-package-for-accessing-rc-transmitters/)

## Running the code

```
rosrun rosserial_python serial_node.py _port:=/dev/ttyACM1 _baud:115200
```

## Launching rosppm
The simplest way to see if usb2ppm is properly working is to use roslaunch
First, launch the roscore in a new terminal window:
```
roscore
```
Next, in a new terminal, run the usb2ppm send_Tx launch file which subscribes channel values and publish it to the transmitter

```
roslaunch rosppm send_Tx.launch
```

For receiving the transmitter channel values, launch the read_Tx launch file which publishes the channel values of the stick inputs of the transmitter

```
roslaunch rosppm read_Tx.launch
```
Finally, to watch the published values from the transmitter, in a new terminal.
```
rostopic echo /rosppm/channels
```

##Install
### Installing Dependencies
- rosserial

To run rosppm package rosserial is used to allow the mcu to communicate with roscore
```
sudo apt-get install ros-{ROS-DISTRO}-rosserial-arduino
sudo apt-get install ros-{ROS-DISTRO}-rosserial
```
Tutorial for rosserial can be found in the [rosserial wiki](http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup)

### Installing rosppm
Install rosppm package by placing the code in the source folder in catkin_ws

```
cd <catkin_workspace>/src
git clone https://github.com/Jaeyoung-Lim/rosppm.git
cd <catkin_workspace>
catkin build  rosppm
```
