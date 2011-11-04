#ifndef __DEPLOYED_COMPONENT_MANAGER_H_INCLUDED__
#define __DEPLOYED_COMPONENT_MANAGER_H_INCLUDED__

#include <smart_cfg_server/deployed_component.h>
#include <smart_cfg_server/deployed_component_id.h>
#include <smart_cfg_server/i_deployed_component_push_reply_listener.h>
#include <smart_cfg_server/i_deployed_component_state_change_listener.h>
#include <smart_cfg_server/i_deployed_component_system_push_handler.h>
#include <smart_cfg_server/parameter_change_request.h>
#include <smart_cfg_server/log.h>
#include <boost/shared_ptr.hpp>
#include <vector>

namespace smart_cfg_server
{

// Class Declaration
class DeployedComponentManager : public IDeployedComponentPushReplyListener, public SharedFrom<DeployedComponentManager>
{
protected:
  boost::weak_ptr<IDeployedComponentStateChangeListener> change_listener_;
  boost::weak_ptr<IDeployedComponentSystemPushHandler> push_handler_;

  typedef std::map<DeployedComponentID, DeployedComponent::Ptr> ComponentListType;
  ComponentListType component_list_;

  bool componentExists( const DeployedComponentID component_id );

public:
  void registerDeployedComponent( const DeployedComponentID component_id );
  void registerChangeListener( boost::weak_ptr<IDeployedComponentStateChangeListener> change_listener );
  void registerPushHandler( boost::weak_ptr<IDeployedComponentSystemPushHandler> push_handler );

  // Override
  void parameterValueOverrideRequest( DeployedComponentID component_id, const ParameterIDAndValue::ListOf& param_list);

  // Called from System Link (The actual value of a parameter)
  void pushReplyReceivedNotify( const DeployedComponentID component_id, const ParameterIDAndValue& param );

  // Called from Robot Model?
  void parameterValueChangeRequest( const DeployedComponentID component_id, const std::vector<ParameterIDAndValue>& param_list );

  // Called from GUI Link
  void triggerFullGuiUpdate( DeployedComponentID component_id );

  // Called from Deployed Components (Childs)
  void parameterStateChangeNotify( const DeployedComponentID& component_id, ParameterIDAndValueEx::WeakConstPtrList& parameter_info );
  void pushChangesToComponents( ParameterChangeRequest::Ptr request );

  // For updateing periodically. Called by?
  void triggerPushChangesToComponents();

};

}

#endif
