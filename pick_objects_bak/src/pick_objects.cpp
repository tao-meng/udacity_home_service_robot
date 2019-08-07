#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = -10.0;
  goal.target_pose.pose.position.y = -2.0;
  goal.target_pose.pose.orientation.w = 1.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending pick-up position as first goal");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();
  
  // whether picked up or not
  bool pickup = false;

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
  {
    ROS_INFO("The robot reached the pick-up point");
	pickup = true;
  }
  else
  {
    ROS_INFO("The robot failed to reach the pick-up point. All goals cancelled");
	ac.cancelAllGoals();
  }
  
  if(pickup)
	{
		// Wait 5 sec for simulating the pick up action
		ros::Duration(5.0).sleep();
		ROS_INFO("Virtual object picked up");

		move_base_msgs::MoveBaseGoal dropoff_goal;
		
		// set up the frame parameters
	    dropoff_goal.target_pose.header.frame_id = "map";
	    dropoff_goal.target_pose.header.stamp = ros::Time::now();

	    // Define a position and orientation for the robot to reach
	    dropoff_goal.target_pose.pose.position.x = -5.0;
		dropoff_goal.target_pose.pose.position.y = -1.0;
	    dropoff_goal.target_pose.pose.orientation.w = 1.0;

		ROS_INFO("Sending drop-off position as second goal");
		ac.sendGoal(dropoff_goal);

		ac.waitForResult();

		if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
		{
			ROS_INFO("The robot reached the drop-off point");
		}
		else
		{
			ROS_INFO("The robot failed to reach the drop-off point");
		}
	}

  return 0;
}