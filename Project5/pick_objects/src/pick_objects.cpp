#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

float pickup[2] = {0.0545, -5.46};
float dropoff[2] = {-0.0164, -10.5};

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
	
	ros::init(argc, argv, "pick_objects");
	MoveBaseClient ac("move_base", true);
	
	while(!ac.waitForServer(ros::Duration(5.0))){
		ROS_INFO("Waiting for the move_base action server to come up");
	}
	
	sleep(10);
	move_base_msgs::MoveBaseGoal goal;
	
	goal.target_pose.header.frame_id = "map";
	goal.target_pose.header.stamp = ros::Time::now();
	goal.target_pose.pose.position.x = pickup[0];
	goal.target_pose.pose.position.y = pickup[1];
	goal.target_pose.pose.orientation.w = 1.0;

	ROS_INFO("Sending goal");
	ac.sendGoal(goal);

	ac.waitForResult();

	if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
		ROS_INFO("Robot picked up the object");
	else
		ROS_INFO("Robot Failed to pick up");


	ros::Duration(5.0).sleep();

	goal.target_pose.pose.position.x = dropoff[0];
	goal.target_pose.pose.position.y = dropoff[1];
	goal.target_pose.pose.orientation.w = 1.0;

	ROS_INFO("Sending second goal");
	ac.sendGoal(goal);

	ac.waitForResult();

	if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
		ROS_INFO("Robot dropped off the object");
	else
		ROS_INFO("Robot failed to drop off object");


	return 0;
}

