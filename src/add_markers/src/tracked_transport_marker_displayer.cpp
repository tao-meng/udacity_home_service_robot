#include "tracked_transport_marker_displayer.hpp"


TrackedTransportMarkerDisplayer::TrackedTransportMarkerDisplayer(SimplifiedPose const & pickup, SimplifiedPose const & dropoff) :
    pickup_pose_{pickup},
    dropoff_pose_{dropoff},
    has_robot_reached_pickup_zone_{false},
    has_robot_reached_dropoff_zone_{false}
{
    FillInMarker(pickup_pose_, pickup_marker_, "pickup_marker");
    FillInMarker(dropoff_pose_, dropoff_marker_, "dropoff_marker");
}

void TrackedTransportMarkerDisplayer::Display()
{
    ros::NodeHandle nh;
    marker_publisher_ = nh.advertise<visualization_msgs::Marker>("visualization_marker", 1);

    // Wait until there is some subscriber
    while (marker_publisher_.getNumSubscribers() < 1)
    {
        if(!ros::ok())
        {
            return;
        }
        ROS_WARN_ONCE("Please create a subscriber to the marker");
        sleep(1);
    }

    // Create and fill in marker for pick-up zone
    PublishMarker(marker_publisher_, pickup_marker_, visualization_msgs::Marker::ADD);
    TrackRobot();
}

void TrackedTransportMarkerDisplayer::TrackRobot()
{
    ros::NodeHandle nh;
    odometry_subscriber_ = nh.subscribe("/odom", 1,
                            &TrackedTransportMarkerDisplayer::TrackingCallback,
                            this);
    ros::spin();
}

void TrackedTransportMarkerDisplayer::TrackingCallback(nav_msgs::Odometry const & odom)
{
    if(has_robot_reached_pickup_zone_)
    {
        if(has_robot_reached_dropoff_zone_)
            return;
        if(IsRobotInPose(odom, dropoff_pose_))
        {
            has_robot_reached_dropoff_zone_ = true;
            PublishMarker(marker_publisher_, dropoff_marker_, visualization_msgs::Marker::ADD);
            return;
        }
    }
    if (IsRobotInPose(odom, pickup_pose_))
    {
        has_robot_reached_pickup_zone_ = true;
        PublishMarker(marker_publisher_, pickup_marker_, visualization_msgs::Marker::DELETE);
    }
}

bool TrackedTransportMarkerDisplayer::IsRobotInPose(
    nav_msgs::Odometry const & odom,
    SimplifiedPose const & pose)
{
    double diff_x = pose.x - odom.pose.pose.position.x;
    double diff_y = pose.y - odom.pose.pose.position.y;
    double sq_distance_to_pickup{diff_x * diff_x  + diff_y * diff_y};
    return sq_distance_to_pickup < constants::kSquaredDistanceThreshold;
}
