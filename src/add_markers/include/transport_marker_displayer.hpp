#pragma once

#include "home_service_robot_common.hpp"
#include "marker_displayer.hpp"

class TransportMarkerDisplayer : public MarkerDisplayer
{
public:
    TransportMarkerDisplayer(SimplifiedPose const & pickup, SimplifiedPose const & dropoff);
    virtual void Display() override;
private:
    ros::Publisher marker_publisher_;
    SimplifiedPose pickup_pose_;
    SimplifiedPose dropoff_pose_;
};
