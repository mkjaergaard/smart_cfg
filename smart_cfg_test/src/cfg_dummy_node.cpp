#include <ros/ros.h>
#include <smart_cfg/parameterized_component_ros.h>

class CfgDummy : smart_cfg::ParameterizedComponentRos
{
  // Ros Stuff
  ros::NodeHandle nh_;

  // Cfg Stuff
  smart_cfg::Parameter<double> param_somefloat;
  smart_cfg::Parameter<int>    param_someint;
  smart_cfg::Parameter<int>    param_someotherint;

public:

  CfgDummy( ros::NodeHandle& nh ) :
    ParameterizedComponentRos( "cfg_dummy", nh ),
    // Ros Stuff
    nh_(nh),
    // Cfg Stuff
    param_somefloat    ( this, "somefloat" ),
    param_someint      ( this, "someint" ),
    param_someotherint ( this, "someotherint" )
  {
  }

  void notifyParametersHasChanged()
  {
    std::cout << "I was told some parameter has changed value" << std::endl;
  }

  void run()
  {
    ros::spin();
  }

};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "cfg_dummy");
  ros::NodeHandle nh("cfg_dummy");
  CfgDummy component(nh);

  component.run();
  return 0;
}
