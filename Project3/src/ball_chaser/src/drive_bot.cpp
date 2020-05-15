#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "ball_chaser/DriveToTarget.h"

ros::Publisher motor_command_publisher;


bool handle_drive_request(ball_chaser::DriveToTarget::Request& req, ball_chaser::DriveToTarget::Response& res)
{
	ROS_INFO("Drive to target request received - linear x: %1.2f, angular z: %1.2f", (float)req.linear_x, (float)req.angular_z);
	
	geometry_msgs::Twist msg;
	msg.linear.x = req.linear_x;
	msg.angular.z=req.angular_z;	
	motor_command_publisher.publish(msg);
	res.msg_feedback = "Requested Velocities set linear x: " + std::to_string(msg.linear.x) + " , angular z: " + std::to_string(msg.angular.z);
	ROS_INFO_STREAM(res.msg_feedback);
	return true;
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "drive_bot");
	ros::NodeHandle n;
	motor_command_publisher=n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
	ros::ServiceServer service = n.advertiseService("/ball_chaser/command_robot", handle_drive_request);
	ros::spin();
	return 0;
}
