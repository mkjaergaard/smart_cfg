#ifndef __PARAMETERIZED_COMPONENT_ROS_H_INCLUDED__
#define __PARAMETERIZED_COMPONENT_ROS_H_INCLUDED__

#include <ros/ros.h>
#include <smart_cfg_msgs/ParameterCtrl.h>
#include <smart_cfg_msgs/DeployedComponentID.h>
#include <smart_cfg/parameterized_component.h>
#include <smart_cfg/parameter.h>
#include <smart_cfg/controlled_component_ros.h>

namespace smart_cfg
{

class ParameterizedComponentRos : public ParameterizedComponent, public ControlledComponentRos
{
protected:
  ros::ServiceServer service_parameter_ctrl_;
  ros::Timer timer_discovery_;
  ros::Publisher pub_discovery_;
  bool discovered_;

protected:
  ~ParameterizedComponentRos() {}

  // Ros Topic handlers
  bool parameterCtrlHandler( smart_cfg_msgs::ParameterCtrl::Request &req, smart_cfg_msgs::ParameterCtrl::Response &res )
  {
    discovered_ = true;

    bool something_changed = false;
    for( smart_cfg_msgs::ParameterCtrl::Request::_set_parameters_type::iterator it = req.set_parameters.begin();
         it != req.set_parameters.end();
         it++ )
    {
      smart_cfg_msgs::ParameterDescriptor& param = *it;
      setParameterValue( param.name, param.type, param.value );
      something_changed = true;
    }

    if( something_changed )
    {
      notifyParametersHasChanged();
    }

    // Empty Request, send all parameter values
    //if( req.set_parameters.size() == 0 )
    {
      for( ParameterListType::iterator it = parameter_list_.begin(); it != parameter_list_.end(); it++ )
      {
        smart_cfg_msgs::ParameterDescriptor desc;
        desc.name = it->second->name();
        desc.type = it->second->type();
        it->second->getEncodedValue(desc.value);
        res.get_parameters.push_back(desc);
      }
    }
    return true;
  }

  void discoveryTimerHandler(const ros::TimerEvent & e)
  {
    if( !discovered_ )
    {
      smart_cfg_msgs::DeployedComponentID myself;
      myself.name = "cfg_dummy";
      pub_discovery_.publish(myself);
    }
  }

public:
  ParameterizedComponentRos( const std::string& component_name, ros::NodeHandle& nh ) :
    ControlledComponentRos( nh ),
    service_parameter_ctrl_( nh.advertiseService("parameter_ctrl", &ParameterizedComponentRos::parameterCtrlHandler, this)),
    timer_discovery_( nh.createTimer( ros::Duration(1.0), &ParameterizedComponentRos::discoveryTimerHandler, this )),
    pub_discovery_( nh.advertise<smart_cfg_msgs::DeployedComponentID>("/register_deployed_component", 1)),
    discovered_( false )
  {

  }


};

}

#endif
