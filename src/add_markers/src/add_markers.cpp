#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "transport_marker_displayer.hpp"
#include "tracked_transport_marker_displayer.hpp"
#include "home_service_robot_common.hpp"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "add_markers");

    // Check parameter configuration
    ros::NodeHandle nh;
    SimplifiedPose pickup;
    SimplifiedPose dropoff;
    if (!ReadPickUpAndDropOffZones(pickup, dropoff))
        return 0;

    // Get mode: default to "track_robot" ( true )
    bool track_robot;
    if (!nh.getParam("/plemma/hsr/add_markers/track_robot", track_robot))
    {
        track_robot = true;
    }

    // Display the markers
    if (track_robot)
    {
        TrackedTransportMarkerDisplayer displayer{pickup, dropoff};
        displayer.Display();
    }
    else
    {
        TransportMarkerDisplayer displayer{pickup, dropoff};
        displayer.Display();
    }
    return 0;
}
