//robot_cleaner.cpp
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <sstream>
using namespace std;

ros::Publisher velocity_publisher;
ros::Subscriber pose_subscriber;
turtlesim::Pose turtlesim_pose;
const double x_min = 0.0;
const double y_min = 0.0;
const double x_max = 11.0;
const double y_max = 11.0;
const double PI = 3.14159265359;

//to move from one point to specified distance
void move(double speedx, double speedy, int diagonal, double distance, bool isForward){
	geometry_msgs::Twist vel_msg;

	//set a random linear velocity in the x-axis
	if (isForward){
		vel_msg.linear.x = abs(speedx);
		vel_msg.linear.y = abs(speedy);
		vel_msg.linear.z = abs(speedy);
}
	else{
		vel_msg.linear.x = -abs(speedx);
		vel_msg.linear.y = -abs(speedy);
		vel_msg.linear.z = -abs(speedy);
}
	

	//set a random angular velocity in teh y-axis
	vel_msg.angular.x = 10;
	//diagonal angle in order to make the move function not move only in x-axis
	vel_msg.angular.y = diagonal;
	vel_msg.angular.z = 10;

	//t0: current time
	double t0 = ros::Time::now().toSec();
	double current_distance = 0.0;
	ros::Rate loop_rate(100);
	double t1;
	do{
	//publish the msg
		velocity_publisher.publish(vel_msg);
		t1 = ros::Time::now().toSec();
		
		if (speedy != 0){
			current_distance = speedy *(t1-t0);
ROS_INFO_STREAM((t1-t0) << "," << current_distance << "," << distance << "," << vel_msg.linear.z << endl);
}
		else {
			current_distance = speedx *(t1-t0);
ROS_INFO_STREAM((t1-t0) << "," << current_distance << "," << distance << "," << vel_msg.linear.x << endl);
}
		ros::spinOnce();
		loop_rate.sleep();
		
	}while(current_distance < distance);
	vel_msg.linear.x = 0;
	vel_msg.linear.y = 0;
	vel_msg.linear.z = 0;
	velocity_publisher.publish(vel_msg);


}
void poseCallback(const turtlesim::Pose::ConstPtr &pose_message){
	turtlesim_pose.x = pose_message -> x;
	turtlesim_pose.y = pose_message -> y;
	turtlesim_pose.theta = pose_message -> theta;
}

void rotate(double angular_speed,double relative_angle, bool clockwise){
geometry_msgs::Twist vel_msg;
	//set a random linear velocity in the x-axis

	vel_msg.linear.x = 1.5; //here****
	vel_msg.linear.y = 0;
	vel_msg.linear.z = 0;
	//set a random angular velocity in the y-axis
	vel_msg.angular.x = 0;
	vel_msg.angular.y = 0;

	if (clockwise)
		vel_msg.angular.z = -abs(angular_speed);
	else
		vel_msg.angular.z = abs(angular_speed);
	double current_angle = 0.0;
	double t0 = ros::Time::now().toSec();
	double t1;
	ros::Rate loop_rate(1000);
	do{
		velocity_publisher.publish(vel_msg);
		t1 = ros::Time::now().toSec();
		current_angle = angular_speed * (t1 - t0);
		ros::spinOnce();
		loop_rate.sleep();
	}while(current_angle < relative_angle);

	vel_msg.angular.z = 0;
	velocity_publisher.publish(vel_msg);
}
double degrees2radians(double angle_in_degrees){
	return angle_in_degrees * PI / 180.0;
}

void spiralClean(double distance){
	geometry_msgs::Twist vel_msg;
	double count = 0;

	double constant_speed = 6.5;//speed
	double vk = 1;
	double wk = 2;
	double rk = 8; //radius
	ros::Rate loop(10);
double t0 = ros::Time::now().toSec();
double current_distance = 0.0;
	do {
		rk = rk+0.1;
		wk = wk + 15;
		vel_msg.linear.x = rk;
		vel_msg.linear.y = 0;
		vel_msg.linear.z = 0;
		//set a random angular velocity in the y-axis
		vel_msg.angular.x = 0;
		vel_msg.angular.y = 0;
		vel_msg.angular.z = constant_speed+2;
		double t1 = ros::Time::now().toSec();
		current_distance = constant_speed *(t1-t0);

	cout << "vel_msg.linear.x = " << vel_msg.linear.x << endl;
	cout << "vel_msg.angular.z = " << vel_msg.angular.z << endl;
	velocity_publisher.publish(vel_msg);
	ros::spinOnce();
	loop.sleep();
	} while(current_distance < distance);
vel_msg.linear.x = 0;
vel_msg.angular.z = 0;
velocity_publisher.publish(vel_msg);

}


int main(int argc, char **argv){
	ros::init(argc,argv,"turtlesim_cleaner");
	ros::NodeHandle n;
	double speed,angular_speed;
	double distance, angle;
	bool isForward, clockwise;
	velocity_publisher = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",1000);
	pose_subscriber = n.subscribe("/turtle1/pose",10,poseCallback);


	ros::Rate loop_rate(20);
	ROS_INFO_STREAM("\n\n\n*****START MOVING *******\n");

//MAKE THE NUMBER 9

	
	angular_speed = 60.0;
	angle = 360.0;
	clockwise = false;
	rotate(degrees2radians(angular_speed), degrees2radians(angle),clockwise);
//	move(0.5,0.5,-30,1.8, true);
//	spiralClean(8);
//	angle = 47.6;
//	clockwise = true;
//	rotate(degrees2radians(angular_speed), degrees2radians(angle),clockwise);
//	move(0.5,0.4,30,.68, true);
//	angle = 99.5;
//	clockwise = true;
//	rotate(degrees2radians(angular_speed), degrees2radians(angle),clockwise);
//	move(0.5,0.5,0,4, true);
	
	/*angular_speed = 2.0;
	angle = 90.0;
	clockwise = false;
//MAKE THE NUMBER 7
	rotate(degrees2radians(angular_speed), degrees2radians(angle),clockwise);
	move(0.5,0.4,1, true);
	clockwise = true;
	rotate(degrees2radians(angular_speed), degrees2radians(angle),clockwise);
	move(0.2,0,2, true);
	clockwise = false;
	rotate(degrees2radians(angular_speed), degrees2radians(angle),clockwise);
	move(0.5,0.4,2, false);*/
	//ros::Rate loop_rate(0.5);
	//loop_rate.sleep();
	//setDesiredOrientation(degrees2radians(60));
	//loop_rate.sleep();
	//setDesiredOrientation(degrees2radians(60));

	loop_rate.sleep();
	ros::spin();
	return 0;
}
