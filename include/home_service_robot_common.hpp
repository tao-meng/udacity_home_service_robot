#pragma once

#include <ros/ros.h>

namespace constants
{
constexpr double kPi = 3.14159265358979323846;
constexpr double kMarkerRedComponent = 0.0;
constexpr double kMarkerGreenComponent = 0.0;
constexpr double kMarkerBlueComponent = 1.0;
constexpr double kMarkerColorAlpha = 1.0;
constexpr double kSquaredDistanceThreshold = 0.2;
} // namespace constants

struct SimplifiedPose
{
    double x;
    double y;
    double yaw_in_deg;
};

inline bool ReadPickUpAndDropOffZones(SimplifiedPose & pickup, SimplifiedPose & dropoff)
{
    // Check parameter configuration
    ros::NodeHandle nh;

    // Get positions: they are required
    if (!( nh.getParam("/plemma/hsr/pickup_pose_x", pickup.x)
        && nh.getParam("/plemma/hsr/pickup_pose_y", pickup.y)
        && nh.getParam("/plemma/hsr/dropoff_pose_x", dropoff.x)
        && nh.getParam("/plemma/hsr/dropoff_pose_y", dropoff.y)))
    {
        ROS_ERROR("Missing positions of pick-up or drop-off zone");
        return false;
    }

    // Get yaw angle: default to 0 if they are not there
    if (!nh.getParam("/plemma/hsr/pickup_pose_yaw_deg", pickup.yaw_in_deg))
    {
        pickup.yaw_in_deg = 0.0;
    }
    if (!nh.getParam("/plemma/hsr/dropoff_pose_yaw_deg", dropoff.yaw_in_deg))
    {
        dropoff.yaw_in_deg = 0.0;
    }
    return true;
}
