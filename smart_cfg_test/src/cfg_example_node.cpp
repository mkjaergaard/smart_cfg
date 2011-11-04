#include <ros/ros.h>
#include <smart_cfg/parameterized_component_ros.h>

class CfgExample : smart_cfg::ParameterizedComponentRos
{
  // Ros Stuff
  ros::NodeHandle nh_;

  // Smart Cfg Stuff
  smart_cfg::Parameter<double> param_somefloat;
  smart_cfg::Parameter<int>    param_someint;

public:
  CfgDummy( ros::NodeHandle& nh ) :
    ParameterizedComponentRos( "cfg_example", nh ),
    // Ros Stuff
    nh_(nh),
    // Cfg Stuff
    param_somefloat    ( this, "somefloat" ),
    param_someint      ( this, "someint" )
  {
  }

  void notifyParametersHasChanged()
  {
    std::cout << "Some parameter has changed value" << std::endl;
    if( param_someint.hasChanged() )
    {
      std::cout << "It was param_someint, new value is: " << param_someint.value() << std::endl;
    }
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
