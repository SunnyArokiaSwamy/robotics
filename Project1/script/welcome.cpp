#include <gazebo/gazebo.hh>

namespace gazebo
{
  class WorldPluginMiniRobot : public WorldPlugin
  {
    public: WorldPluginMiniRobot() : WorldPlugin()
            {
              printf("Welcome to Sunny's World!\n");
            }

    public: void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf)
            {
            }
  };
  GZ_REGISTER_WORLD_PLUGIN(WorldPluginMiniRobot)
}
