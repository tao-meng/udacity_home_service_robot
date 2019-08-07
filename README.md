# udacity_home_service_robot
Home Service Robot project at udacity

---
# Fix the environment problem

As I mentioned at: https://knowledge.udacity.com/questions/52586, I'm stuck at "Simulation Setup" step.

solution: just switch the env at minicoda3 manually **everytime in the Terminal** before you do and further actions, like catkin_make, etc.

`conda activate /opt/robond/py2` 

---
# Mapping

Here are steps how to launch it:

1. open a Terminal with the correct python environment
2. cd /home/workspace/catkin_ws
3. source devel/setup.bash   !!! do not forget it
4. source src/scripts/**test_slam.sh**

I used my own world file which was created in previous project:

`xterm -e " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/workspace/catkin_ws/src/map/myoffice.world " &`

It contians following packages:

- **turtlebot_gazebo**, a turtlebot with in my world environment
- **gmapping**, a **gmapping** demo to perform SLAM
- **turtlebot_rviz_launchers**, a rviz with a configuration that will show navigation
- **turtlebot_teleop** with keyboard_teleop, a node that will allow you to command the turtlebot with your keyboard

---
# Localization and Navigation

Here are steps how to launch it:

1. open a Terminal with the correct python environment
2. cd /home/workspace/catkin_ws
3. source devel/setup.bash   !!! do not forget it
4. source src/scripts/**test_navigation.sh**

We launched 3 things:

- **turtlebot_world** with in my world in gazebo
- **amcl_demo**, localize the turtlebot
- **view_navigation**, observe the map in viz

just in viz and try to select "2D Nav Goal" button and locate it wherever in the map you want the robot to move.

As mentioned in the lesson **Localization and Navigation Testing**: We will be using the ROS Navigation stack, which is based on the Dijkstra's, a variant of the Uniform Cost Search algorithm, to plan our robot trajectory from start to goal position. 

It works for me, great~~



---
# Create 2 of ROS Nodes

#### pick_objects

Here are steps how to launch it:

1. open a Terminal with the correct python environment
2. cd /home/workspace/catkin_ws
3. source devel/setup.bash   !!! do not forget it
4. source src/scripts/**pick_objects.sh**

The purpose of this script is simulating the scenario that the robot will navigate to the first place to pick up sth and the drop off into the second place.


#### add_markers

Here are steps how to launch it:

1. open a Terminal with the correct python environment
2. cd /home/workspace/catkin_ws
3. source devel/setup.bash   !!! do not forget it
4. source src/scripts/**add_markers.sh**

This mode is basically the testing phase of our node. The behaviour expected is:

- Show marker in pick-up zone for 5 seconds
- Hide marker
- Wait 5 seconds
- Show marker in drop-off zone

It works for me, great~~


---
# Home Service Robot

Integrate everything together!

Here are steps how to launch it:

1. open a Terminal with the correct python environment
2. cd /home/workspace/catkin_ws
3. source devel/setup.bash   !!! do not forget it
4. source src/scripts/**home_service.sh**

- Robot can localize itself and navigate through the map
- It goes to the pick up zone, marked with a blue marker visible in rviz
- Once there, the marker disappears and the robot waits for 5 seconds, simulating picking up the virtual object
- The robot goes then to the drop-off zone
- Once there, a blue marker is displayed

It works for me, great~~


