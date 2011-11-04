#ifndef __MIDDLEWARE_GUI_LINK_ROS_H_INCLUDED__
#define __MIDDLEWARE_GUI_LINK_ROS_H_INCLUDED__

#include <smart_cfg_server/middleware_gui_link.h>
#include <smart_cfg_server/parameter_id.h>
#include <smart_cfg_server/deployed_component_id.h>
#include <smart_cfg_server/parameter_id_and_value_ex.h>
#include <smart_cfg_server/deployed_component_manager.h>
#include <smart_cfg_msgs/ComponentModelInfoRequest.h>
#include <smart_cfg_msgs/DeployedComponentInfo.h>
#include <smart_cfg_msgs/OverrideRequest.h>
#include <smart_cfg_server/log.h>
#include <ros/ros.h>

class MiddlewareGuiLinkRos : public smart_cfg_server::MiddlewareGuiLink
{
protected:
  ros::NodeHandle nh_;
  ros::Timer poll_timer_;
  ros::Publisher pub_componentinfo_;
  ros::Subscriber sub_request_componentinfo_;
  ros::Subscriber sub_parameter_override_;

  typedef std::set<DeployedComponentID> RequestedComponentListType;
  RequestedComponentListType requested_component_list_;

protected:
  void requestComponentInfoHandler( const smart_cfg_msgs::ComponentModelInfoRequest::ConstPtr& req )
  {
    DeployedComponentID component_id(req->component_id.name);
    RequestedComponentListType::iterator current = requested_component_list_.find(component_id);
    if( req->subscribe )
    {
      smart_cfg_server::Log::Info("Gui Subscribe Request for Component", component_id.getText());
      // Only insert into set if its not there already
      if ( current == requested_component_list_.end() )
      {
        requested_component_list_.insert( component_id );
      }
      // todo: send all info about component
      if( !deployed_component_mngr_.expired() )
      {
        boost::shared_ptr<smart_cfg_server::DeployedComponentManager>(deployed_component_mngr_)->triggerFullGuiUpdate( component_id );
      }
    }
    else
    {
      smart_cfg_server::Log::Info("Gui Unsubscribe Request for Component", component_id.getText());
    }
  }

  void requestParameterOverride( const smart_cfg_msgs::OverrideRequest::ConstPtr& req )
  {
    DeployedComponentID component_id(req->component_id.name);
    smart_cfg_server::Log::Info("Parameter Override Request", component_id.getText());
    std::vector<ParameterIDAndValue> param_list;
    for ( smart_cfg_msgs::OverrideRequest::_parameters_type::const_iterator it = req->parameters.begin(); it != req->parameters.end(); it++ )
    {
      ParameterIDAndValue param( (*it).id.name );
      param.value().setFromEncodedValue( (*it).value.encoded_value, (*it).value.type);
      param_list.push_back( param );
    }
    // call something?
    boost::shared_ptr<smart_cfg_server::DeployedComponentManager>(deployed_component_mngr_)->parameterValueOverrideRequest( component_id, param_list );
  }

public:
  // Called by component manager
  // Impl of IDeployedComponentChangeListener
  void parameterStateChangeNotify( const DeployedComponentID& component_id, ParameterIDAndValueEx::WeakConstPtrList& parameter_info )
  {
    if( requested_component_list_.find(component_id) != requested_component_list_.end() )
    {
      // todo: send all info about component
      smart_cfg_msgs::DeployedComponentInfo::Ptr msg(new smart_cfg_msgs::DeployedComponentInfo());
      msg->id.name = component_id.getText();
      msg->model_id.name = ""; // todo:
      for( ParameterIDAndValueEx::WeakConstPtrList::iterator it = parameter_info.begin(); it != parameter_info.end(); it++ )
      {
        // todo, check it weak ptr is alive
        ParameterIDAndValueEx::ConstPtr param = (*it).lock();
        smart_cfg_msgs::ParameterIDAndValueEx param_msg;
        param_msg.id.name = param->getName();
        param_msg.current_value.encoded_value = param->value().getEncodedValue();
        param_msg.current_value.type = param->value().getType();
        param_msg.change_request = param->hasPendingChange();
        param_msg.new_value.encoded_value = param->newValue().getEncodedValue();
        param_msg.new_value.type = param->newValue().getType();
        msg->parameters.push_back(param_msg);
      }
      pub_componentinfo_.publish(msg);
    }
  }


  MiddlewareGuiLinkRos(ros::NodeHandle& nh) :
    nh_(nh),
    pub_componentinfo_         ( nh_.advertise<smart_cfg_msgs::DeployedComponentInfo>("/deployed_component_info", 5) ),
    sub_request_componentinfo_ ( nh_.subscribe<smart_cfg_msgs::ComponentModelInfoRequest>("/deployed_component_info_request", 5, &MiddlewareGuiLinkRos::requestComponentInfoHandler, this) ),
    sub_parameter_override_    ( nh_.subscribe<smart_cfg_msgs::OverrideRequest>("/parameter_override", 5, &MiddlewareGuiLinkRos::requestParameterOverride, this) )
  {

  }

};

#endif
