#ifndef __MIDDLEWARE_SYSTEM_LINK_ROS_H_INCLUDED__
#define __MIDDLEWARE_SYSTEM_LINK_ROS_H_INCLUDED__

#include <smart_cfg_server/middleware_system_link.h>
#include <smart_cfg_msgs/ParameterRequest.h>
#include <smart_cfg_msgs/ParameterDescriptor.h>
#include <smart_cfg_msgs/DeployedComponentID.h>
#include <ros/ros.h>
#include <vector>

class MiddlewareSystemLinkRos : public smart_cfg_server::MiddleWareSystemLink
{
  ros::NodeHandle nh_;
  ros::Timer poll_timer_;
  ros::Subscriber sub_register_deployed_component_;

  // we do the work in a timer event, and empties the queue
  void polled_work(const ros::TimerEvent& event)
  {
    ParameterChangeRequest::ConstPtr request_out;
    if( popChangeRequest(request_out) )
    {
      // Create Request with parameters to change
      smart_cfg_msgs::ParameterRequest::Request srv_request;
      for( ParameterChangeRequest::NewValuesListType::const_iterator it = request_out->newValuesList().begin();
           it != request_out->newValuesList().end();
           it++ )
      {
        const ParameterIDAndValue& param = (*it);
        smart_cfg_msgs::ParameterDescriptor desc;

        desc.name = param.getName();
        desc.type = param.value().getType();
        desc.value = param.value().getEncodedValue();

        srv_request.set_parameters.push_back(desc);
      }

      // Send the request
      smart_cfg_msgs::ParameterRequest::Response srv_response;
      ros::service::call( std::string("/")+request_out->id().getText()+std::string("/list_parameters"), srv_request, srv_response );

      // Callback on all replied parameters
      // todo: what to do in case of errors?

      for( unsigned int i = 0; i < srv_response.get_parameters.size(); i++ )
      {
        smart_cfg_msgs::ParameterDescriptor& srv_param = srv_response.get_parameters.at(i);
        ParameterIDAndValue param(srv_param.name);
        std::cout << srv_param.name << " ; " << srv_param.value << std::endl;
        param.value().setFromEncodedValue(srv_param.value, srv_param.type);
        smart_cfg_server::MiddleWareSystemLink::triggerPushReplyReceivedNotify( request_out->id(), param );
      }
    }
  }

  // This part receives messages from components supporting smart parameters.
  // After getting a registration with this topic, the cfg_server sends a request to receive all parameters from
  // the component. At this point the component knows that it has been registered.
  void registerDeployedComponentHandler( const smart_cfg_msgs::DeployedComponentID::ConstPtr& id )
  {
    std::cout << "--- Registered Component " << id->name << std::endl;
    ParameterChangeRequest::ConstPtr request_out;
    ros::service::call( std::string("/")+id->name+std::string("/list_parameters"), srv_request, srv_response );
  }

 public:
 MiddlewareSystemLinkRos(ros::NodeHandle& nh) : nh_(nh),
    poll_timer_( nh.createTimer(ros::Duration(0.5), &MiddlewareSystemLinkRos::polled_work, this) ),
    sub_register_deployed_component_( nh_.subscribe<smart_cfg_msgs::DeployedComponentID>("/register_deployed_component", 5, &MiddlewareSystemLinkRos::registerDeployedComponentHandler, this) )
  {

  }

};

#endif
