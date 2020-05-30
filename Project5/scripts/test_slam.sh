#!/bin/sh

xterm -e " source devel/setup.bash; export ROBOT_INITIAL_POSE='-x 0 -y 0 -Y 1.5707'; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$PWD/src/turtlebot_simulator/turtlebot_gazebo/worlds/sb.world " &
sleep 5

xterm -e " source devel/setup.bash; rosrun gmapping slam_gmapping " &
sleep 5

xterm -e " source devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch " &
sleep 5

xterm -e " source devel/setup.bash; roslaunch turtlebot_teleop keyboard_teleop.launch " &




