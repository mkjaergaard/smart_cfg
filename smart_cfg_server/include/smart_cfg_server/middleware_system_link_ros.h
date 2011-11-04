#ifndef __MIDDLEWARE_SYSTEM_LINK_ROS_H_INCLUDED__
#define __MIDDLEWARE_SYSTEM_LINK_ROS_H_INCLUDED__

#include <smart_cfg_server/middleware_system_link.h>
#include <smart_cfg_msgs/ParameterRequest.h>
#include <smart_cfg_msgs/ParameterDescriptor.h>
#include <ros/ros.h>
#include <vector>

class MiddlewareSystemLinkRos : public smart_cfg_server::MiddleWareSystemLink
{
  ros::NodeHandle nh_;
  ros::Timer poll_timer_;

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

public:
  MiddlewareSystemLinkRos(ros::NodeHandle& nh) :
    nh_(nh),
    poll_timer_( nh.createTimer(ros::Duration(0.5), &MiddlewareSystemLinkRos::polled_work, this) )
  {

  }

};

#endif
