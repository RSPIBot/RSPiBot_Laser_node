
//http://docs.ros.org/api/sensor_msgs/html/msg/LaserScan.html
#include "ros/ros.h"
#include <stdlib.h>  
#include "std_msgs/String.h"
#include <sensor_msgs/LaserScan.h>

ros::Publisher laser_pub;

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
	sensor_msgs::LaserScan scan;
	
	scan.angle_min = -0.1;
	scan.angle_max = 0.1;
	scan.angle_increment = 0.2;
	
	scan.range_min = 0.0;
	scan.range_max = 0.8;
	scan.ranges.resize(1);
	scan.ranges[0] = (float)atoi(msg->data.c_str());
	
	laser_pub.publish(scan);
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "RSPiBot_Laser_Node", ros::init_options::AnonymousName);
	
	ros::NodeHandle n;
	
	laser_pub = n.advertise<sensor_msgs::LaserScan>("/rspibot/laserscan", 1000);
	
	//sensor_msgs::LaserScan
	
	ros::Subscriber sub = n.subscribe("/rspibotarduino/D", 1000, chatterCallback);
	
	ros::spin();
	return 0;
}
