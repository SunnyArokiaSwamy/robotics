#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include "sensor_msgs/Image.h"

ros::ServiceClient client;
ball_chaser::DriveToTarget drive;

void drive_robot(float lin_x, float ang_z){
  drive.request.linear_x = lin_x;
  drive.request.angular_z = ang_z;
  client.call(drive);

}


void process_image_callback(const sensor_msgs::Image img)
{
  int white_pixel = 255;
  int left_side = 0;
  int right_side = 0;
  int center_side = 0;
  for(int i=0; i <img.height*img.step; i=i+3) 
  {

   

     if(img.data[i] == white_pixel && img.data[i+1] == white_pixel && img.data[i+2] == white_pixel) 
     {
      	if(i%img.step>0 && i%img.step<img.step/3)
        	left_side=left_side+1;
	else if(i%img.step>img.step*2/3)
		right_side=right_side+1;
	else
		center_side=center_side+1;
     }
  }  
  ROS_INFO("left: %d,    Center: %d,    Right:%d", left_side, center_side, right_side);
  if(left_side>center_side && left_side>right_side)
	drive_robot(0.05,0.2);
  if(center_side>left_side && center_side>right_side)
	drive_robot(0.2,0);
  if(right_side>left_side && right_side>center_side)
	drive_robot(0.05,-0.2);
  if(left_side==0 && center_side==0 && right_side==0)
	drive_robot(0,0);
}



int main(int argc, char** argv)
{
 ros::init(argc, argv, "process_image");
 ros::NodeHandle n;

 client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");
 
 ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10 , process_image_callback);
 
 ros::spin();

 return 0;
}
