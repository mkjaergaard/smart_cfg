#ifndef __PARAMETERIZED_COMPONENT_ROS_H_INCLUDED__
#define __PARAMETERIZED_COMPONENT_ROS_H_INCLUDED__

#include <smart_cfg/parameterized_component.h>
#include <smart_cfg/parameter.h>
#include <ros/ros.h>
#include <smart_cfg_msgs/ParameterRequest.h>
#include <smart_cfg/controlled_component_ros.h>

namespace smart_cfg
{

class ParameterizedComponentRos : public ParameterizedComponent, public ControlledComponentRos
{
protected:
  ros::ServiceServer list_service_;

  // Ros Topic handlers
  bool listServiceHandler( smart_cfg_msgs::ParameterRequest::Request &req, smart_cfg_msgs::ParameterRequest::Response &res )
  {
    bool something_changed = false;
    for( smart_cfg_msgs::ParameterRequest::Request::_set_parameters_type::iterator it = req.set_parameters.begin();
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
        desc.name = it->second->getId().getAsText();
        //desc.type = it->second->getValue().getType();
        //desc.value = it->second->getValue().getEncodedValue();
        res.get_parameters.push_back(desc);
      }
    }
    return true;
  }

public:
  ParameterizedComponentRos( const std::string& componentName, ros::NodeHandle& nh ) :
    ControlledComponentRos( nh ),
    list_service_( nh.advertiseService("list_parameters", &ParameterizedComponentRos::listServiceHandler, this))
  {

  }


};

}

#endif
