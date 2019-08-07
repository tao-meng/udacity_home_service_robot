#pragma once

#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

#include "home_service_robot_common.hpp"

class MarkerDisplayer
{
public:
    typedef int32_t ActionType;

    virtual void Display() = 0;

    void FillInMarker(SimplifiedPose const & pose, visualization_msgs::Marker & marker, std::string const & name)
    {
        marker.ns = name;
        marker.id = 0;
        marker.type = visualization_msgs::Marker::CUBE;

        marker.header.frame_id = "map";

        marker.pose.position.x = pose.x;
        marker.pose.position.y = pose.y;
        marker.pose.position.z = 0.0;

        double yaw_in_rad = 2.0 * pose.yaw_in_deg * constants::kPi / 180.0;

        marker.pose.orientation.x = 0.0;
        marker.pose.orientation.y = 0.0;
        marker.pose.orientation.z = std::sin(0.5 * yaw_in_rad);
        marker.pose.orientation.w = std::cos(0.5 * yaw_in_rad);

        marker.scale.x = 0.5;
        marker.scale.y = 0.5;
        marker.scale.z = 0.2;

        marker.color.r = constants::kMarkerRedComponent;
        marker.color.g = constants::kMarkerGreenComponent;
        marker.color.b = constants::kMarkerBlueComponent;
        marker.color.a = constants::kMarkerColorAlpha;

        marker.lifetime = ros::Duration();
    }

    void PublishMarker(ros::Publisher & publisher, visualization_msgs::Marker & marker, ActionType action)
    {
        marker.action = action;
        marker.header.stamp = ros::Time::now();
        publisher.publish(marker);
    }
};
