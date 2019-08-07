#pragma once
#include <nav_msgs/Odometry.h>
#include "marker_displayer.hpp"

class TrackedTransportMarkerDisplayer : public MarkerDisplayer
{
public:
    TrackedTransportMarkerDisplayer(SimplifiedPose const & pickup, SimplifiedPose const & dropoff);
    virtual void Display() override;
private:
    void TrackRobot();
    void TrackingCallback(nav_msgs::Odometry const & odom);
    bool IsRobotInPose(nav_msgs::Odometry const & odom,
                       SimplifiedPose const & pose);

    ros::Publisher marker_publisher_;
    ros::Subscriber odometry_subscriber_;
    visualization_msgs::Marker pickup_marker_;
    visualization_msgs::Marker dropoff_marker_;
    SimplifiedPose pickup_pose_;
    SimplifiedPose dropoff_pose_;
    bool has_robot_reached_pickup_zone_;
    bool has_robot_reached_dropoff_zone_;
};
