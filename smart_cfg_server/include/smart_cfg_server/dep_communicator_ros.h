#ifndef __COMMUNICATOR_ROS_H_INCLUDED__
#define __COMMUNICATOR_ROS_H_INCLUDED__

#include <smart_cfg_server/communicator.h>
#include <smart_cfg/ParameterRequest.h>
#include <smart_cfg/ParameterDescriptor.h>
#include <ros/ros.h>
#include <vector>

class CommunicatorRos : public smart_cfg_server::Communicator
{
  ros::NodeHandle nh_;
  ros::Timer poll_timer_;

  void polled_work(const ros::TimerEvent& event)
  {
    ParameterChangeRequest::ConstPtr request_out;
    if( popParameterChangeRequest(request_out) )
    {
      // Create Request with parameters to change
      smart_cfg::ParameterRequest::Request srv_request;
      for( ParameterChangeRequest::NewValuesListType::const_iterator it = request_out->getNewValuesList().begin();
           it != request_out->getNewValuesList().end();
           it++ )
      {
        const ParameterIDAndValue& param = (*it);
        smart_cfg::ParameterDescriptor desc;

        desc.name = param.name();
        desc.type = param.value().getType();
        desc.value = param.value().getEncodedValue();

        srv_request.set_parameters.push_back(desc);
      }

      // Send the request
      smart_cfg::ParameterRequest::Response srv_response;
      ros::service::call( std::string("/")+request_out->component_name()+std::string("/list_parameters"), srv_request, srv_response );

      // Callback on all replied parameters
      // todo: what to do in case of errors?

      for( unsigned int i = 0; i < srv_response.get_parameters.size(); i++ )
      {
        smart_cfg::ParameterDescriptor& srv_param = srv_response.get_parameters.at(i);
        ParameterIDAndValue param(srv_param.name);
        std::cout << srv_param.name << " ; " << srv_param.value << std::endl;
        param.value().setFromEncodedValue(srv_param.value, srv_param.type);
        smart_cfg_server::Communicator::triggerPushReplyReceivedNotify( request_out->component_name(), param );
      }

    }
  }

public:
  CommunicatorRos(ros::NodeHandle& nh) :
    nh_(nh),
    poll_timer_( nh.createTimer(ros::Duration(0.5), &CommunicatorRos::polled_work, this) )
  {

  }

};

#endif
