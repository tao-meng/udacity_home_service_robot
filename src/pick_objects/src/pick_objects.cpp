#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include "home_service_robot_common.hpp"

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
void FillInGoal(SimplifiedPose const & pose, move_base_msgs::MoveBaseGoal & goal)
{
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();
    goal.target_pose.pose.position.x = pose.x;
    goal.target_pose.pose.position.y = pose.y;
    goal.target_pose.pose.position.z = 0.0;

    double yaw_in_rad = 2.0 * pose.yaw_in_deg * constants::kPi / 180.0;

    goal.target_pose.pose.orientation.x = 0.0;
    goal.target_pose.pose.orientation.y = 0.0;
    goal.target_pose.pose.orientation.z = std::sin(0.5 * yaw_in_rad);
    goal.target_pose.pose.orientation.w = std::cos(0.5 * yaw_in_rad);
}

int main(int argc, char** argv)
{
    // Initialize a ROS node
    ros::init(argc, argv, "pick_objects");

    // Create action client to communicate with action "move_base" and instruct
    // it to start a thread to call ros::spin() (instead of us having to call it
    // manually)
    MoveBaseClient action_client("move_base", true);

    // Wait for the action server to come up
    while(!action_client.waitForServer(ros::Duration(5.0)))
    {
        ROS_INFO("Waiting for the move_base action server to come up");
    }

    // Check parameter configuration
    ros::NodeHandle nh;
    SimplifiedPose pickup;
    SimplifiedPose dropoff;
    if (!ReadPickUpAndDropOffZones(pickup, dropoff))
        return 0;

    move_base_msgs::MoveBaseGoal pickup_goal;

    FillInGoal(pickup, pickup_goal);

    ROS_INFO("Sending pick-up position as first goal");
    action_client.sendGoal(pickup_goal);

    action_client.waitForResult();

    bool pickup_reached = false;

    if(action_client.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    {
        ROS_INFO("The robot reached the pick-up point");
        pickup_reached = true;
    }
    else
    {
        ROS_INFO("The robot failed to reach the pick-up point. All goals cancelled");
        action_client.cancelAllGoals();
    }

    if (pickup_reached)
    {
        ros::Duration(5.0).sleep();
        ROS_INFO("Virtual object picked up");

        move_base_msgs::MoveBaseGoal dropoff_goal;
        FillInGoal(dropoff, dropoff_goal);

        ROS_INFO("Sending drop-off position as second goal");
        action_client.sendGoal(dropoff_goal);

        action_client.waitForResult();

        if(action_client.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
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
