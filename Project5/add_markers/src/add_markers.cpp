#include<ros/ros.h>
#include<visualization_msgs/Marker.h>
#include<nav_msgs/Odometry.h>
#include<math.h>

uint32_t shape = visualization_msgs::Marker::CUBE;
visualization_msgs::Marker marker;
visualization_msgs::Marker marker1;
float pickup[2] = {0.0545, -5.46};
float dropoff[2] = {-0.0164, -10.5};
int flag=1;
float dist = 0;
ros::Publisher marker_pub;

void add_markers_callback(const nav_msgs::Odometry::ConstPtr &msg)
{	

	if(flag)
	{
		ROS_INFO("location x = %f    y = %f ", msg->pose.pose.position.x, msg->pose.pose.position.y);
		dist = sqrt(pow(pickup[0] - msg->pose.pose.position.x,2) + pow(pickup[1] - msg->pose.pose.position.y,2));
		ROS_INFO("Pick up %f", dist);
		sleep(1);
	
		if(dist>0.3)
		{
			marker_pub.publish(marker);
		}
		else
		{
			marker.color.a = 0.0;		
			marker_pub.publish(marker);
			flag = 0;
		}
	}	
	else	
	{
		ROS_INFO("location x = %f    y = %f ", msg->pose.pose.position.x, msg->pose.pose.position.y);
		dist = sqrt(pow(dropoff[0] - msg->pose.pose.position.x,2) + pow(dropoff[1] - msg->pose.pose.position.y,2));
		ROS_INFO("Drop off %f", dist);
		sleep(1);

		if(dist>0.3)
		{
			marker.color.a = 0.0;	
			marker_pub.publish(marker);
		}
		else
		{
			marker.pose.position.x = dropoff[0];
			marker.pose.position.y = dropoff[1];
			marker.pose.position.z = 0;
			marker.color.a = 1.0;		
			marker_pub.publish(marker);
			flag = 0;
		}

	}
	

}

int main(int argc, char** argv)
{

	ros::init(argc, argv, "add_markers");
	ros::NodeHandle n;
	ros::Rate r(1);
	marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

	while (marker_pub.getNumSubscribers() < 1)
	{
		if(!ros::ok())
		{
			return 0;
		}
		ROS_WARN_ONCE("Please create a subscriber to the marker");
		sleep(1);
	}
	
	marker.header.frame_id = "/map";
	marker.header.stamp = ros::Time::now();
	marker.ns = "add_markers";
	marker.id = 0;
	marker.type = shape;
	marker.action = visualization_msgs::Marker::ADD;
	marker.scale.x = 0.5;
	marker.scale.y = 0.5;
	marker.scale.z = 0.5;
	marker.color.r = 0.0f;
	marker.color.g = 0.0f;
	marker.color.b = 1.0f;
	marker.color.a = 1.0;
	marker.pose.position.x = 0.0545;
	marker.pose.position.y = -5.46;
	marker.pose.position.z = 0;
	marker.pose.orientation.x = 0.0;
	marker.pose.orientation.y = 0.0;
	marker.pose.orientation.z = 0.0;
	marker.pose.orientation.w = 1.0;
	marker.lifetime = ros::Duration();
	
	ros::Subscriber sub1 = n.subscribe("/odom", 10, add_markers_callback);
	ros::spin();
}
