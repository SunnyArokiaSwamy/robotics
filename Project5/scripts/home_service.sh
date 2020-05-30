#!/bin/sh


xterm -e " source /home/workspace/catkin_ws/devel/setup.bash; export ROBOT_INITIAL_POSE='-x 0 -y 0 -Y 1.5707'; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/workspace/catkin_ws/src/turtlebot_simulator/turtlebot_gazebo/worlds/sb.world " &
sleep 5

xterm -e " source /home/workspace/catkin_ws/devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch map_file:=/home/workspace/catkin_ws/src/turtlebot_simulator/turtlebot_gazebo/maps/map.yaml" &
sleep 5

xterm -e " source /home/workspace/catkin_ws/devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch " &
sleep 5

xterm -e " source /home/workspace/catkin_ws/devel/setup.bash; rosrun add_markers add_markers " &
sleep 5 

xterm -e " source /home/workspace/catkin_ws/devel/setup.bash; rosrun pick_objects pick_objects "
sleep 5




