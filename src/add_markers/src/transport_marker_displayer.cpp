#include "transport_marker_displayer.hpp"

TransportMarkerDisplayer::TransportMarkerDisplayer(SimplifiedPose const & pickup, SimplifiedPose const & dropoff) :
    pickup_pose_{pickup},
    dropoff_pose_{dropoff}
{}

void TransportMarkerDisplayer::Display()
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
    visualization_msgs::Marker pickup_marker;
    FillInMarker(pickup_pose_, pickup_marker, "pickup_marker");

    ROS_INFO("Adding pick-up marker");
    PublishMarker(marker_publisher_, pickup_marker, visualization_msgs::Marker::ADD);

    ros::Duration(5.0).sleep();

    ROS_INFO("Deleting pick-up marker");
    PublishMarker(marker_publisher_, pickup_marker, visualization_msgs::Marker::DELETE);

    // Wait while the pretended pick-up process happens
    ros::Duration(5.0).sleep();

    // Create and fill in marker for drop-off zone
    visualization_msgs::Marker dropoff_marker;
    FillInMarker(dropoff_pose_, dropoff_marker, "dropoff_marker");

    ROS_INFO("Adding drop-off marker");
    PublishMarker(marker_publisher_, dropoff_marker, visualization_msgs::Marker::ADD);
}
